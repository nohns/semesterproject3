#ifndef DMC_NETLINK_HANDLER_H
#define DMC_NETLINK_HANDLER_H

#include <net/genetlink.h>

#include "../event.h"
#include "event_msg.h"

/**
 * @brief Generic netlink handler for drinks machine
 */
struct dmc_netlink_handler
{
  /**
   * @brief Function pointer to the event handler
   */
  int (*on_event_recv)(struct dmc_base_event        *event,
                       struct dmc_netlink_event_msg *from_msg);

  /**
   * @brief The generic netlink family for the drinks machine. This is set on
   * register and unset on unregister
   */
  struct genl_family *genl_fam;
};

/**
 * @brief Register netlink handler with the driver
 * @handler: The netlink handler to register
 */
int dmc_register_netlink_handler(struct dmc_netlink_handler *handler);

/**
 * @brief Unregister current netlink handler
 */
void dmc_unregister_netlink_handler(struct dmc_netlink_handler *handler);

/**
 * @brief Publish an event mesage to all listeners (multicast)
 * @handler:   The netlink handler to use for publishing the event
 * @event_msg: The event message to publish
 */
int dmc_netlink_publish_event(const struct dmc_netlink_handler *handler,
                              struct dmc_netlink_event_msg     *event_msg);

/**
 * @brief Allocate and prepare a netlink event message for broadcasting.
 * @event_msg: Pointer to the event message to be prepared.
 */
int dmc_netlink_prepare_event(struct dmc_netlink_event_msg *event_msg);

#endif // DMC_NETLINK_HANDLER_H