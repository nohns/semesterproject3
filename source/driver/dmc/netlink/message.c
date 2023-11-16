#include "message.h"
#include <net/genetlink.h>

/* ################################# */
/*    Defining netlink attributes    */
/*       for netlink messages        */
/* ################################# */

#define DMC_EVENT_GENL_BASE_ATTR_TYPE 1
#define __DMC_EVENT_GENL_BASE_ATTR_MAX 1

enum dmc_event_nl_container_weight_measured_attr
{
  DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_UNSPECIFIED = 0,
  DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_TYPE =
      DMC_EVENT_GENL_BASE_ATTR_TYPE,
  DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER = 2,
  DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT = 3,
  __DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_MAX,
};

enum dmc_event_nl_out_of_order_attr
{
  DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_UNSPECIFIED = 0,
  DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_TYPE = DMC_EVENT_GENL_BASE_ATTR_TYPE,
  DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_MESSAGE = 2,
  DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_REASON = 3,
  __DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_MAX,
};

enum dmc_event_nl_user_confirm_attr
{
  DMC_EVENT_GENL_USER_CONFIRM_ATTR_UNSPECIFIED = 0,
  DMC_EVENT_GENL_USER_CONFIRM_ATTR_TYPE = DMC_EVENT_GENL_BASE_ATTR_TYPE,
  __DMC_EVENT_GENL_USER_CONFIRM_ATTR_MAX,
};

enum dmc_event_nl_fluid_pour_requested_attr
{
  DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_UNSPECIFIED = 0,
  DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_TYPE = DMC_EVENT_GENL_BASE_ATTR_TYPE,
  DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER = 2,
  DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT = 3,
  __DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_MAX,
};

/* ################################# */
/*    Functions for UNMARSHALLING    */
/*  from netlink messages to events  */
/* ################################# */

static struct nla_policy base_event_pol[__DMC_EVENT_GENL_BASE_ATTR_MAX + 1] = {
    [DMC_EVENT_GENL_BASE_ATTR_TYPE] = {.type = NLA_NUL_STRING},
};

int dmc_netlink_unmarshal_base_event(struct dmc_base_event *base,
                                     struct dmc_netlink_event_msg *event_msg)
{
  int err;

  // Validate that base is valid
  err = nla_validate(*event_msg->attrs, __DMC_EVENT_GENL_BASE_ATTR_MAX,
                     NLA_TYPE_MAX, base_event_pol, NULL);
  if (err != 0)
    return err;

  // Unmarshal data
  base->type = *(u8 *)nla_data(event_msg->attrs[DMC_EVENT_GENL_BASE_ATTR_TYPE]);

  return 0;
}

int dmc_netlink_unmarshal_event_user_confirm(
    struct dmc_event_user_confirm *event,
    struct dmc_netlink_event_msg *event_msg)
{
  return 0;
}

static struct nla_policy event_fluid_pour_requested_pol
    [__DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_MAX] = {
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER] = {.type = NLA_U8},
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT] = {.type = NLA_U8},
};

int dmc_netlink_unmarshal_event_fluid_pour_requested(
    struct dmc_event_fluid_pour_requested *event,
    struct dmc_netlink_event_msg *event_msg)
{
  int err;

  // Validate that this even is a valid
  err = nla_validate(*event_msg->attrs,
                     __DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_MAX,
                     NLA_TYPE_MAX, event_fluid_pour_requested_pol, NULL);
  if (err != 0)
    return err;

  // Unmarshal data
  event->container = *(u8 *)nla_data(
      event_msg->attrs[DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER]);
  event->amount = *(u8 *)nla_data(
      event_msg->attrs[DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT]);

  return 0;
}

/* ################################# */
/*     Functions for MARSHALLING     */
/*  from netlink messages to events  */
/* ################################# */

/**
 * @brief Marshal base event into generic netlink message
 */
int dmc_netlink_marshal_base_event(struct dmc_netlink_event_msg *event_msg,
                                   struct dmc_base_event *base)
{
  int err;
  err = nla_put_u8(event_msg->buff, DMC_EVENT_GENL_BASE_ATTR_TYPE,
                   (u8)base->type);
  if (err != 0)
    return err;

  return 0;
}

int dmc_netlink_marshal_event_container_weight_measured(
    struct dmc_netlink_event_msg *event_msg,
    struct dmc_event_container_weight_measured *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0)
    return err;

  // - MARK: Marshal event specific fields

  // Container
  err = nla_put_u8(event_msg->buff,
                   DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER,
                   event->container);
  if (err != 0)
    return err;

  // Weight
  err = nla_put_s16(event_msg->buff,
                    DMC_EVENT_GENL_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT,
                    event->weight);
  if (err != 0)
    return err;

  return 0;
}

int dmc_netlink_marshal_event_out_of_order(
    struct dmc_netlink_event_msg *event_msg,
    struct dmc_event_out_of_order *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0)
    return err;

  // - MARK: Marshal event specific fields

  // Message
  err =
      nla_put_string(event_msg->buff, DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_MESSAGE,
                     event->message);
  if (err != 0)
    return err;

  // Reason
  err = nla_put_u8(event_msg->buff, DMC_EVENT_GENL_OUT_OF_ORDER_ATTR_REASON,
                   event->reason);
  if (err != 0)
    return err;

  return 0;
}

int dmc_genl_marshal_event_user_confirm(struct dmc_netlink_event_msg *event_msg,
                                        struct dmc_event_user_confirm *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0)
    return err;

  return 0;
}