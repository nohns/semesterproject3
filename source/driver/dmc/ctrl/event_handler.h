#ifndef DMC_CTRL_EVENT_HANDLER_H
#define DMC_CTRL_EVENT_HANDLER_H

#include "../event.h"
#include "../uart/handler.h"

/**
 * @brief A struct defining the dependencies of the control event handler
 */
struct dmc_ctrl_event_handler
{
  struct dmc_uart_handler *uart;
};

/**
 * @brief Handles receiving a user confirm event from user space
 * program.
 * @returns 0 on success, negative on failure
 */
int dmc_ctrl_on_event_user_confirm(struct dmc_ctrl_event_handler *evt_handler,
                                   struct dmc_event_user_confirm *event);

/**
 * @brief Handles receiving a fluid poor requested event from user space
 * program.
 * @returns 0 on success, negative on failure
 */
int dmc_ctrl_on_event_fluid_pour_requested(
    struct dmc_ctrl_event_handler *evt_handler,
    struct dmc_event_fluid_pour_requested *event);

#endif // DMC_CTRL_EVENT_HANDLER_H