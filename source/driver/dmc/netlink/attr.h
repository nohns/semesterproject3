#ifndef DMC_NETLINK_ATTR_H
#define DMC_NETLINK_ATTR_H

/* ################################# */
/*    Defining netlink attributes    */
/*       for netlink messages        */
/* ################################# */

#define DMC_EVENT_GENL_BASE_ATTR_TYPE 1
#define __DMC_EVENT_GENL_BASE_ATTR_MAX 1

enum dmc_genl_event_genl_attr
{
  DMC_GENL_EVENT_ATTR_UNSPECIFIED,

  // - Base event attributes -

  DMC_GENL_EVENT_BASE_ATTR_TYPE,

  // - Container weight measured event attributes -

  DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER,
  DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT,

  // - Out of order event attributes -

  DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE,
  DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON,

  // - User confirm event attributes -

  DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER,
  DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT,

  __DMC_GENL_EVENT_ATTR_MAX,
};

#endif /* DMC_NETLINK_ATTR_H */