#ifndef DMC_CTRL_EVENT_HANDLER_H
#define DMC_CTRL_EVENT_HANDLER_H

#include "../netlink/handler.h"
#include "../uart/handler.h"
#include "event.h"

#include "packet.h"

struct ctrl_event_handler
{
  struct dmc_netlink_handler *nl_handler;
  struct dmc_uart_handler    *uart;
};

int ctrl_on_event_fluid_pour_requested(
    struct ctrl_event_handler             *evt_handler,
    struct dmc_event_fluid_pour_requested *event);

#endif // DMC_CTRL_EVENT_HANDLER_H