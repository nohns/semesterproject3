#include <linux/init.h>   /* Needed for the macros */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/module.h>
#include <linux/module.h> /* Needed by all modules */
#include <net/genetlink.h>

#include "dmc/ctrl/event_handler.h"
#include "dmc/ctrl/packet_handler.h"
#include "dmc/netlink/handler.h"
#include "dmc/netlink/message.h"
#include "dmc/out_of_order.h"
#include "dmc/uart/handler.h"
#include "dmc/util.h"
#include "packet.h"

// Forward declarations
static int dmc_netlink_handle_event(struct dmc_base_event        *base,
                                    struct dmc_netlink_event_msg *from_msg);
static int dmc_uart_recv_byte(u8 data);

// Struct defining the drinks machine netlink handler. This points to the event
// handler function
static struct dmc_netlink_handler nl_handler = {
    .on_event_recv = dmc_netlink_handle_event,
};

static struct dmc_ctrl_event_handler  evt_handler = {};
static struct dmc_ctrl_packet_handler pck_handler = {
    .nl_handler = &nl_handler,
};

// Handle incoming events from rpi via netlink
static int dmc_netlink_handle_event(struct dmc_base_event        *base_event,
                                    struct dmc_netlink_event_msg *from_msg)
{
  int err;
  pr_debug("Received event from netlink! type: %d\n", base_event->type);

  // Unmarshal event into specific event based on received event type.
  // Afterwards, call the appropriate control event handler function
  switch (base_event->type)
  {
  case DMC_EVENT_TYPE_USER_CONFIRM:
  {
    struct dmc_base_event out_of_order_base = {
        .type = DMC_EVENT_TYPE_USER_CONFIRM,
    };
    struct dmc_event_user_confirm event = {
        .base = &out_of_order_base,
    };
    err = dmc_netlink_unmarshal_event_user_confirm(&event, from_msg);
    if (err != 0) break;

    pr_debug("dmc_driver: recv user confirm event\n");

    // Call the event handler
    err = dmc_ctrl_on_event_user_confirm(&evt_handler, &event);
    if (err != 0)
    {
      pr_debug("dmc_driver: failed to handle user confirm event, err = %d\n",
               err);
      break;
    }
    break;
  }
  case DMC_EVENT_TYPE_FLUID_POUR_REQUESTED:
  {
    struct dmc_base_event out_of_order_base = {
        .type = DMC_EVENT_TYPE_OUT_OF_ORDER,
    };
    struct dmc_event_fluid_pour_requested event = {
        .base = &out_of_order_base,
    };
    err = dmc_netlink_unmarshal_event_fluid_pour_requested(&event, from_msg);
    if (err != 0) break;

    pr_debug(
        "dmc_driver: recv fluid poor requested event for container %d with "
        "amount %d\n",
        event.container, event.amount);

    // Call the event handler
    err = dmc_ctrl_on_event_fluid_pour_requested(&evt_handler, &event);
    break;
  }
  case DMC_EVENT_TYPE_DEBUG:
  {
    struct dmc_event_debug event;
    err = dmc_netlink_unmarshal_event_debug(&event, from_msg);
    if (err != 0) break;

    pr_debug("dmc_driver: recv debug event with event type %d\n",
             event.event_type);

    switch ((enum dmc_event_type)event.event_type)
    {
    case DMC_EVENT_TYPE_OUT_OF_ORDER:
    {
      char   *message;
      uint8_t reason = event.data;
      switch (event.data)
      {
      case 2:
        pr_debug("dmc_driver: debug event data is 1\n");
        message = DMC_OUT_OF_ORDER_MESSAGE_REASON_FLUID_CONTAINER_1_REMOVED;
        break;
      case 3:
        pr_debug("dmc_driver: debug event data is 2\n");
        message = DMC_OUT_OF_ORDER_MESSAGE_REASON_FLUID_CONTAINER_2_REMOVED;
        break;
      case 4:
        pr_debug("dmc_driver: debug event data is 3\n");
        message = DMC_OUT_OF_ORDER_MESSAGE_REASON_FLUID_CONTAINER_3_REMOVED;
        break;
      case 1:
      default:
        message = DMC_OUT_OF_ORDER_MESSAGE_REASON_UNKNOWN;
        reason  = 1;
        break;
      }

      struct dmc_base_event out_of_order_base = {
          .type = DMC_EVENT_TYPE_OUT_OF_ORDER,
      };
      struct dmc_event_out_of_order out_of_order_event = {
          .base    = &out_of_order_base,
          .message = message,
          .reason  = reason,
      };

      // Prepare new netlink event message
      struct dmc_netlink_event_msg nl_msg;
      err = dmc_netlink_prepare_event(&nl_msg, out_of_order_base.type);
      if (err != 0) return err;

      // Marshal event into netlink event message
      err =
          dmc_netlink_marshal_event_out_of_order(&nl_msg, &out_of_order_event);
      if (err != 0)
      {
        pr_debug("dmc_driver: debug failed to marshal event. err = %d\n", err);
        return err;
      }

      // Publish event
      err = dmc_netlink_publish_event(&nl_handler, &nl_msg);
      if (err != 0)
      {
        pr_debug("dmc_driver: debug failed to publish event. err = %d\n", err);
        return err;
      }
      break;
    }
    case DMC_EVENT_TYPE_CONTAINER_VOLUME_MEASURED:
    {
      struct dmc_base_event weight_base = {
          .type = DMC_EVENT_TYPE_CONTAINER_VOLUME_MEASURED,
      };
      struct dmc_event_container_volume_measured weight_event = {
          .base      = &weight_base,
          .container = 2,
          .volume    = event.data,
      };

      // Prepare new netlink event message
      struct dmc_netlink_event_msg nl_msg;
      err = dmc_netlink_prepare_event(&nl_msg, weight_base.type);
      if (err != 0) return err;

      // Marshal event into netlink event message
      err = dmc_netlink_marshal_event_container_volume_measured(&nl_msg,
                                                                &weight_event);
      if (err != 0)
      {
        pr_debug("dmc_driver: debug failed to marshal event. err = %d\n", err);
        return err;
      }

      // Publish event
      err = dmc_netlink_publish_event(&nl_handler, &nl_msg);
      if (err != 0)
      {
        pr_debug("dmc_driver: debug failed to publish event. err = %d\n", err);
        return err;
      }

      break;
    }
    default:
      pr_debug("dmc_driver: debug event type %d not handled\n",
               event.event_type);
      break;
    }

    break;
  }
  default:
    pr_notice("dmc_driver: received non-handled event type %d from netlink\n",
              base_event->type);
    break;
  }

  // If error was set during handling of event, propagate it
  if (err != 0) return err;

  return 0;
}

static int dmc_uart_handle_packet(struct dmc_packet *base_packet)
{
  int err;

  // Unmarshal packet into specific packet based on received packet type.
  // Afterwards, call the appropriate control packet handler function
  switch (base_packet->type)
  {
  case DMC_PACKET_OUT_OF_ORDER:
  {

    struct dmc_packet_out_of_order packet;
    err = dmc_packet_unmarshal_out_of_order(&packet, base_packet);
    if (err != 0) break;

    pr_debug("dmc_driver: recv packet out of order with reason %d\n",
             packet.reason);

    // Call the packet handler
    err = dmc_ctrl_on_packet_out_of_order(&pck_handler, &packet);
    break;
  }
  case DMC_PACKET_CONTAINER_VOLUME_MEASURED:
  {
    struct dmc_packet_container_volume_measured packet;
    err = dmc_packet_unmarshal_container_volume_measured(&packet, base_packet);
    if (err != 0) break;

    pr_debug(
        "dmc_driver: recv packet vol measured for container %d with vol %d\n",
        packet.container, packet.volume);

    // Call the packet handler
    err = dmc_ctrl_on_packet_container_volume_measured(&pck_handler, &packet);
    break;
  }
  case DMC_PACKET_MACHINE_OK:
  {
    struct dmc_packet_machine_ok packet;
    err = dmc_packet_unmarshal_machine_ok(&packet, base_packet);
    if (err != 0) break;

    pr_debug("dmc_driver: recv packet machine ok\n");

    // Call the packet handler
    err = dmc_ctrl_on_packet_machine_ok(&pck_handler, &packet);
    break;
  }
  default:
    pr_notice("dmc_driver: received non-handled packet type %d from netlink\n",
              base_packet->type);
    break;
  }

  // If error was set during handling of packet, propagate it
  if (err != 0) return err;

  return 0;
}

// The currently being received packet
static struct dmc_packet *curr_packet = NULL;

static int dmc_uart_recv_byte(u8 data)
{
  // pr_debug("dmc_driver: received byte %d\n", data);
  if (data == 0)
  {
    // pr_debug("dmc_driver: received byte 0, ignoring\n");
    return 0;
  }

  // Start new packet if no packet is currently being received
  if (curr_packet == NULL)
  {
    // If starting data byte is not one of the expected type, just dont do
    // anything
    if (data != DMC_PACKET_OUT_OF_ORDER &&
        data != DMC_PACKET_CONTAINER_VOLUME_MEASURED &&
        data != DMC_PACKET_USER_CONFIRM &&
        data != DMC_PACKET_FLUID_POUR_REQUESTED && data != DMC_PACKET_DEBUG &&
        data != DMC_PACKET_MACHINE_OK)
      return -1;

    // pr_debug("dmc_driver: starting new packet\n");
    curr_packet = dmc_packet_init(data);

    // If packet is not complete, we gotta get some more data before handling
    // it
    if (!dmc_packet_complete(curr_packet))
    {
      return 0;
    }

    // Handle the complete packet and deallocate it afterwards
    int err = dmc_uart_handle_packet(curr_packet);
    dmc_packet_free(curr_packet);
    curr_packet = NULL;

    // If error was set during handling of packet, propagate it
    if (err != 0) return err;

    return 0;
  }

  // Add byte to packet
  dmc_packet_append_byte(curr_packet, data);
  // pr_debug("dmc_driver: appended data bey. len now %ld\n",
  //          curr_packet->data_len);

  // If packet is complete, handle it
  if (dmc_packet_complete(curr_packet))
  {
    // pr_debug("dmc_driver: packet complete with %ld data bytes. Now handling "
    //          "packet...\n",
    //          curr_packet->data_len);

    // Handle the complete packet and deallocate it afterwards
    int err = dmc_uart_handle_packet(curr_packet);
    dmc_packet_free(curr_packet);
    curr_packet = NULL;

    // If error was set during handling of packet, propagate it
    if (err != 0) return err;
    return 0;
  }

  return 0;
}

static int __init dmc_init(void)
{
  int err;
  pr_info("dmc_driver: initializing...\n");

  // Register drinks machine netlink handler
  err = dmc_register_netlink_handler(&nl_handler);
  if (err != 0)
    ERRGOTO(fail_dmc_init_reg_netlink_handler,
            "dmc_driver: failed to register netlink handler\n");

  // Register drinks machine uart handler
  err = dmc_uart_handler_register(dmc_uart_recv_byte);
  if (err != 0)
    ERRGOTO(fail_dmc_init_reg_uart_handler,
            "dmc_driver: failed to register uart handler\n");

  // Register drinks machine control event handler
  /*err = dmc_ctrl_event_handler_register(&evt_handler);
   if (err != 0)
     ERRGOTO(fail_dmc_init_reg_ctrl_evt_handler,
             "dmc_driver: failed to register event handler\n");

   // Register drinks machine control packet handler
   err = dmc_ctrl_packet_handler_register(&pck_handler);
   if (err != 0)
     ERRGOTO(fail_dmc_init_reg_ctrl_pck_handler,
             "dmc_driver: failed to register packet handler\n");*/

  // Success!
  pr_info("dmc_driver: initialized successfully!\n");
  return 0;

// Goto error handling...
/*fail_dmc_init_reg_ctrl_pck_handler:
  dmc_ctrl_event_handler_unregister(&evt_handler);
fail_dmc_init_reg_ctrl_evt_handler:
  dmc_uart_handler_unregister();*/
fail_dmc_init_reg_uart_handler:
  dmc_unregister_netlink_handler(&nl_handler);
fail_dmc_init_reg_netlink_handler:
  return err;
}

static void __exit dmc_exit(void)
{
  pr_info("dmc_driver: unloading...\n");

  // Unregister drinks machine control packet handler
  // dmc_ctrl_packet_handler_unregister(&pck_handler);

  // Unregister drinks machine control event handler
  // dmc_ctrl_event_handler_unregister(&evt_handler);

  // Unregister drinks machine uart handler
  dmc_uart_handler_unregister();

  // Unregister drinks machine netlink handler
  dmc_unregister_netlink_handler(&nl_handler);

  // GOODBYE :(
  pr_info("dmc_driver: unloaded! goodbye...\n");
}

// Setup module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Semesterprojekt gruppe 14");
MODULE_DESCRIPTION("Driver responsible for communicating with the Ultimate "
                   "Drinks Machine(TM)");

// Register init and exit functions
module_init(dmc_init);
module_exit(dmc_exit);
