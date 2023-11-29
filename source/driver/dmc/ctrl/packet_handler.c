#include "packet_handler.h"

#include "../event.h"
#include "../netlink/message.h"
#include "../out_of_order.h"

int dmc_ctrl_on_packet_out_of_order(struct dmc_ctrl_packet_handler *pck_handler,
                                    struct dmc_packet_out_of_order *packet)
{
  int err;

  pr_debug("ctrl on out of order before switch\n");

  // Decide what text message to include in event
  char *message;
  switch (packet->reason)
  {
  case DMC_PACKET_OUT_OF_ORDER_REASON_UNKNOWN:
  {
    message = DMC_OUT_OF_ORDER_MESSAGE_REASON_UNKNOWN;
    break;
  }
  case DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_1_REMOVED:
  {
    message = DMC_OUT_OF_ORDER_MESSAGE_REASON_FLUID_CONTAINER_1_REMOVED;
    break;
  }
  case DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_2_REMOVED:
  {
    message = DMC_OUT_OF_ORDER_MESSAGE_REASON_FLUID_CONTAINER_2_REMOVED;
    break;
  }
  case DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_3_REMOVED:
  {
    message = DMC_OUT_OF_ORDER_MESSAGE_REASON_FLUID_CONTAINER_3_REMOVED;
    break;
  }
  default:
  {
    message = DMC_OUT_OF_ORDER_MESSAGE_REASON_UNKNOWN;
    break;
  }
  }

  pr_debug("ctrl on out of order before event init\n");

  // Create event representation of packet
  struct dmc_base_event base = {
      .type = DMC_EVENT_TYPE_OUT_OF_ORDER,
  };
  struct dmc_event_out_of_order event = {
      .base    = &base,
      .message = message,
      .reason  = packet->reason,
  };

  pr_debug("ctrl on out of order before prepare nl msg\n");

  // Prepare new netlink event message
  struct dmc_netlink_event_msg nl_msg;
  err = dmc_netlink_prepare_event(&nl_msg, event.base->type);
  if (err != 0) return err;

  pr_debug("ctrl on out of order before marshal event\n");

  // Marshal event into netlink event message
  err = dmc_netlink_marshal_event_out_of_order(&nl_msg, &event);
  if (err != 0) return err;

  pr_debug("ctrl on out of order before publish event\n");

  // Publish event
  err = dmc_netlink_publish_event(pck_handler->nl_handler, &nl_msg);
  if (err != 0) return err;

  return 0;
}

int dmc_ctrl_on_packet_container_weight_measured(
    struct dmc_ctrl_packet_handler              *pck_handler,
    struct dmc_packet_container_weight_measured *packet)
{
  int err;

  // Create event representation of packet
  struct dmc_base_event base = {
      .type = DMC_EVENT_TYPE_CONTAINER_WEIGHT_MEASURED,
  };
  struct dmc_event_container_weight_measured event = {
      .base      = &base,
      .container = packet->container,
      .weight    = packet->weight,
  };

  // Prepare new netlink event message
  struct dmc_netlink_event_msg nl_msg;
  err = dmc_netlink_prepare_event(&nl_msg, event.base->type);
  if (err != 0) return err;

  // Marshal event into netlink event message
  err = dmc_netlink_marshal_event_container_weight_measured(&nl_msg, &event);
  if (err != 0) return err;

  // Publish event
  err = dmc_netlink_publish_event(pck_handler->nl_handler, &nl_msg);
  if (err != 0) return err;

  return 0;
}

int dmc_ctrl_on_packet_machine_ok(struct dmc_ctrl_packet_handler *pck_handler,
                                  struct dmc_packet_machine_ok   *packet)
{
  int err;

  // Create event representation of packet
  struct dmc_base_event base = {
      .type = DMC_EVENT_TYPE_MACHINE_OK,
  };
  struct dmc_event_machine_ok event = {
      .base = &base,
  };

  // Prepare new netlink event message
  struct dmc_netlink_event_msg nl_msg;
  err = dmc_netlink_prepare_event(&nl_msg, event.base->type);
  if (err != 0) return err;

  // Marshal event into netlink event message
  err = dmc_genl_marshal_event_machine_ok(&nl_msg, &event);
  if (err != 0) return err;

  // Publish event
  err = dmc_netlink_publish_event(pck_handler->nl_handler, &nl_msg);
  if (err != 0) return err;

  return 0;
}