#ifndef DMC_NETLINK_POLICY_H
#define DMC_NETLINK_POLICY_H

#include <net/genetlink.h>

#include "attr.h"

#define DMC_EVENT_GENL_BASE_POLICY_ATTR_TYPE NLA_U8

// Command policy for raise liquid pour requested
static const struct nla_policy dmc_genl_policy_liquid_pour_requested
    [__DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_MAX] = {
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE] =
            {.type = DMC_EVENT_GENL_BASE_POLICY_ATTR_TYPE},
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER] = {.type = NLA_U8},
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT]    = {.type = NLA_U8},

};

// Command policy for raise user confirm
static const struct nla_policy dmc_genl_policy_user_confirm
    [__DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_MAX] = {
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE] =
            {.type = DMC_EVENT_GENL_BASE_POLICY_ATTR_TYPE},
};

#endif // DMC_NETLINK_POLICY_H