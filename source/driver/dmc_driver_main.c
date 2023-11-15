#include <linux/module.h>

#include "dmc/netlink/handler.h"
#include "dmc/netlink/message.h"
#include "dmc/uart/handler.h"
#include "dmc/util.h"

// Forward delcaration
static int dmc_netlink_handle_event(struct dmc_base_event        *base,
                                    struct dmc_netlink_event_msg *from_msg);

// Struct defining the drinks machine netlink handler. This points to the event
// handler function
static struct dmc_netlink_handler nl_handler = {
    .on_event_recv = dmc_netlink_handle_event,
};

// Handle incoming events from rpi via netlink
static int dmc_netlink_handle_event(struct dmc_base_event        *base,
                                    struct dmc_netlink_event_msg *from_msg)
{
  int err;

  switch (base->type)
  {
  case DMC_EVENT_TYPE_USER_CONFIRM:
  {
    struct dmc_event_user_confirm event;
    err = dmc_netlink_unmarshal_event_user_confirm(&event, from_msg);
    if (err != 0) return err;

    struct dmc_base_event new_event_base = {
        .type = DMC_EVENT_TYPE_CONTAINER_WEIGHT_MEASURED,
    };
    struct dmc_event_container_weight_measured new_event = {
        .base      = &new_event_base,
        .container = 1,
        .weight    = 2,
    };

    // Prepare new netlink event message
    struct dmc_netlink_event_msg new_msg;
    err = dmc_netlink_prepare_event(&new_msg);
    if (err != 0) return err;

    // Marshal event into netlink event message
    err = dmc_netlink_marshal_event_container_weight_measured(&new_msg,
                                                              &new_event);
    if (err != 0) return err;

    // Send event to rpi
    err = dmc_netlink_publish_event(&nl_handler, &new_msg);
    if (err != 0) return err;

    break;
  }
  default:
    break;
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

  // Success!
  pr_info("dmc_driver: initialized successfully!\n");
  return 0;

// Goto error handling...
fail_dmc_init_reg_netlink_handler:
  return err;
}

static void __exit dmc_exit(void)
{
  pr_info("dmc_driver: unloading...\n");

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
