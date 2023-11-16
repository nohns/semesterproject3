#include <linux/module.h>

#include "dmc/ctrl/event_handler.h"
#include "dmc/ctrl/packet_handler.h"
#include "dmc/netlink/handler.h"
#include "dmc/netlink/message.h"
#include "dmc/uart/handler.h"
#include "dmc/util.h"
#include "packet.h"

// Forward declarations
static int dmc_netlink_handle_event(struct dmc_base_event *base,
                                    struct dmc_netlink_event_msg *from_msg);
static int dmc_uart_recv_byte(u8 data);

// Struct defining the drinks machine netlink handler. This points to the event
// handler function
static struct dmc_netlink_handler nl_handler = {
    .on_event_recv = dmc_netlink_handle_event,
};

static struct dmc_uart_handler uart_handler = {
    .on_byte_recv = dmc_uart_recv_byte,
};

static struct dmc_ctrl_event_handler evt_handler = {
    .uart = &uart_handler,
};

static struct dmc_ctrl_packet_handler pck_handler = {
    .nl_handler = &nl_handler,
};

// Handle incoming events from rpi via netlink
static int dmc_netlink_handle_event(struct dmc_base_event *base_event,
                                    struct dmc_netlink_event_msg *from_msg)
{
  int err;

  // Unmarshal event into specific event based on received event type.
  // Afterwards, call the appropriate control event handler function
  switch (base_event->type)
  {
  case DMC_EVENT_TYPE_USER_CONFIRM:
  {
    struct dmc_event_user_confirm event;
    err = dmc_netlink_unmarshal_event_user_confirm(&event, from_msg);
    if (err != 0)
      break;

    // Call the event handler
    err = dmc_ctrl_on_event_user_confirm(&evt_handler, &event);
    break;
  }
  case DMC_EVENT_TYPE_FLUID_POUR_REQUESTED:
  {
    struct dmc_event_fluid_pour_requested event;
    err = dmc_netlink_unmarshal_event_fluid_pour_requested(&event, from_msg);
    if (err != 0)
      break;

    // Call the event handler
    err = dmc_ctrl_on_event_fluid_pour_requested(&evt_handler, &event);
    break;
  }
  default:
    pr_notice("dmc_driver: received non-handled event type %d from netlink\n",
              base_event->type);
    break;
  }

  // If error was set during handling of event, propagate it
  if (err != 0)
    return err;

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
    if (err != 0)
      break;

    // Call the packet handler
    err = dmc_ctrl_on_packet_out_of_order(&pck_handler, &packet);
    break;
  }
  case DMC_PACKET_CONTAINER_WEIGHT_MEASURED:
  {
    struct dmc_packet_container_weight_measured packet;
    err = dmc_packet_unmarshal_container_weight_measured(&packet, base_packet);
    if (err != 0)
      break;

    // Call the packet handler
    err = dmc_ctrl_on_packet_container_weight_measured(&pck_handler, &packet);
    break;
  }
  default:
    pr_notice("dmc_driver: received non-handled packet type %d from netlink\n",
              base_packet->type);
    break;
  }

  // If error was set during handling of packet, propagate it
  if (err != 0)
    return err;

  return 0;
}

// The currently being received packet
static struct dmc_packet *curr_packet = NULL;

static int dmc_uart_recv_byte(u8 data)
{
  // Start new packet if no packet is currently being received
  if (curr_packet == NULL)
  {
    curr_packet = dmc_packet_init(data);
  }

  // If packet is complete, handle it
  if (dmc_packet_complete(curr_packet))
  {
    // Handle the complete packet and deallocate it afterwards
    int err = dmc_uart_handle_packet(curr_packet);
    dmc_packet_free(curr_packet);
    curr_packet = NULL;

    // If error was set during handling of packet, propagate it
    if (err != 0)
      return err;
    return 0;
  }

  // Add byte to packet
  dmc_packet_append_byte(curr_packet, data);

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
  err = dmc_uart_handler_register(&uart_handler);
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
  dmc_uart_handler_unregister(&uart_handler);*/
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
  dmc_uart_handler_unregister(&uart_handler);

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
