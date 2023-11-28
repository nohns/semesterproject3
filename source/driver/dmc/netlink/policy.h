#ifndef DMC_NETLINK_POLICY_H
#define DMC_NETLINK_POLICY_H

#include <net/genetlink.h>

#include "attr.h"

#define DMC_EVENT_GENL_BASE_POLICY_ATTR_TYPE NLA_U8

static const struct nla_policy dmc_genl_event_pol[__DMC_GENL_EVENT_ATTR_MAX] = {
    [DMC_GENL_EVENT_ATTR_UNSPECIFIED] = {.type = NLA_UNSPEC},

    // - Base event attributes -

    [DMC_GENL_EVENT_BASE_ATTR_TYPE] = {.type = NLA_U8},

    // - Container weight measured event attributes -

    [DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER] = {.type =
                                                                     NLA_U8},
    [DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT] = {.type = NLA_S16},

    // - Out of order event attributes -

    [DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE] = {.type = NLA_NUL_STRING},
    [DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON]  = {.type = NLA_U8},

    // - Fluid pour requested event attributes -

    [DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER] = {.type = NLA_U8},
    [DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT]    = {.type = NLA_U8},

    // - Debug event attributes -
    [DMC_GENL_EVENT_DEBUG_ATTR_EVENT_TYPE] = {.type = NLA_U8},
    [DMC_GENL_EVENT_DEBUG_ATTR_DATA]       = {.type = NLA_U8},
};

#endif // DMC_NETLINK_POLICY_H
