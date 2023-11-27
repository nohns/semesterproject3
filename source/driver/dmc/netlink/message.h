#ifndef DMC_NETLINK_MESSAGE_H
#define DMC_NETLINK_MESSAGE_H

#include <linux/skbuff.h>
#include <net/genetlink.h>

#include "../event.h"
#include "event_msg.h"

/* ################################# */
/*    Functions for unmarshalling    */
/*  from netlink messages to events  */
/* ################################# */

/**
 * @brief Unmarshal base event from netlink message
 */
int dmc_netlink_unmarshal_base_event(struct dmc_base_event        *event,
                                     struct dmc_netlink_event_msg *event_msg);

/**
 * @brief Unmarshal user confirm event from netlink message
 */
int dmc_netlink_unmarshal_event_user_confirm(
    struct dmc_event_user_confirm *event,
    struct dmc_netlink_event_msg  *event_msg);

/**
 * @brief Unmarshal fluid pour requested event from netlink message
 */
int dmc_netlink_unmarshal_event_fluid_pour_requested(
    struct dmc_event_fluid_pour_requested *event,
    struct dmc_netlink_event_msg          *event_msg);

/**
 * @brief Unmarshal machine ok event from netlink message
 */
int dmc_netlink_unmarshal_event_machine_ok(
    struct dmc_event_machine_ok  *event,
    struct dmc_netlink_event_msg *event_msg);

/**
 * @brief Unmarshal debug event from netlink message
 */
int dmc_netlink_unmarshal_event_debug(struct dmc_event_debug       *event,
                                      struct dmc_netlink_event_msg *event_msg);

/* ################################# */
/*     Functions for marshalling     */
/*  from netlink messages to events  */
/* ################################# */

/**
 * @brief Marshal container weight measured event into generic netlink message
 */
int dmc_netlink_marshal_event_container_weight_measured(
    struct dmc_netlink_event_msg               *event_msg,
    struct dmc_event_container_weight_measured *event);

/**
 * @brief Marshal out of order event into generic netlink message
 */
int dmc_netlink_marshal_event_out_of_order(
    struct dmc_netlink_event_msg  *event_msg,
    struct dmc_event_out_of_order *event);

#endif // DMC_NETLINK_MESSAGE_H