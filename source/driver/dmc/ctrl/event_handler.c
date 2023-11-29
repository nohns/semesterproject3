

#include "event_handler.h"

int dmc_ctrl_on_event_user_confirm(struct dmc_ctrl_event_handler *evt_handler,
                                   struct dmc_event_user_confirm *event)
{
  int err;

  // Create packet representation of event
  struct dmc_packet_user_confirm packet;

  // Marshal specific packet into base packet form
  struct dmc_packet *base_packet = NULL;
  err = dmc_packet_marshal_user_confirm(base_packet, &packet);
  if (err != 0)
  {
    // Avoid memory leak if packet has been allocated
    if (base_packet != NULL) dmc_packet_free(base_packet);
    return err;
  }

  // Send packet to rpi over uart
  err = dmc_uart_handler_send_packet(base_packet);
  dmc_packet_free(base_packet); // Free before err check
  if (err != 0) return err;

  return 0;
}

int dmc_ctrl_on_event_fluid_pour_requested(
    struct dmc_ctrl_event_handler         *evt_handler,
    struct dmc_event_fluid_pour_requested *event)
{
  int err;

  // Create packet representation of event
  struct dmc_packet_fluid_pour_requested packet = {
      .container = event->container,
      .amount    = event->amount,
  };

  // Marshal specific packet into base packet form
  struct dmc_packet *base_packet = NULL;
  err = dmc_packet_marshal_fluid_pour_requested(base_packet, &packet);
  if (err != 0)
  {
    // Avoid memory leak if packet has been allocated
    if (base_packet != NULL) dmc_packet_free(base_packet);
    return err;
  }

  // Send packet to rpi over uart
  err = dmc_uart_handler_send_packet(base_packet);
  dmc_packet_free(base_packet); // Free before err check
  if (err != 0) return err;

  return 0;
}
