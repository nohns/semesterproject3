#include "packet_handler.h"

#include "../event.h"
#include "../netlink/message.h"
#include "../out_of_order.h"

int dmc_ctrl_on_packet_out_of_order(struct dmc_ctrl_packet_handler *pck_handler,
                                    struct dmc_packet_out_of_order *packet)
{
  int err;

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
  }

  // Create event representation of packet
  struct dmc_event_out_of_order event = {
      .message = message,
      .reason  = packet->reason,
  };

  // Prepare new netlink event message
  struct dmc_netlink_event_msg nl_msg;
  err = dmc_netlink_prepare_event(&nl_msg);
  if (err != 0) return err;

  // Marshal event into netlink event message
  err = dmc_netlink_marshal_event_out_of_order(&nl_msg, &event);
  if (err != 0) return err;

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
  struct dmc_event_container_weight_measured event = {
      .container = packet->container,
      .weight    = packet->weight,
  };

  // Prepare new netlink event message
  struct dmc_netlink_event_msg nl_msg;
  err = dmc_netlink_prepare_event(&nl_msg);
  if (err != 0) return err;

  // Marshal event into netlink event message
  err = dmc_netlink_marshal_event_container_weight_measured(&nl_msg, &event);
  if (err != 0) return err;

  // Publish event
  err = dmc_netlink_publish_event(pck_handler->nl_handler, &nl_msg);
  if (err != 0) return err;

  return 0;
}