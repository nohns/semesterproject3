#include "message.h"
#include <net/genetlink.h>

#include "attr.h"

/* ################################# */
/*    Functions for UNMARSHALLING    */
/*  from netlink messages to events  */
/* ################################# */

/*static struct nla_policy base_event_pol[__DMC_EVENT_GENL_BASE_ATTR_MAX + 1] =
{ [DMC_EVENT_GENL_BASE_ATTR_TYPE] = {.type = NLA_NUL_STRING},
};*/

int dmc_netlink_unmarshal_base_event(struct dmc_base_event        *base,
                                     struct dmc_netlink_event_msg *event_msg)
{
  // Unmarshal data
  base->type = *(u8 *)nla_data(event_msg->attrs[DMC_GENL_EVENT_BASE_ATTR_TYPE]);

  return 0;
}

int dmc_netlink_unmarshal_event_user_confirm(
    struct dmc_event_user_confirm *event,
    struct dmc_netlink_event_msg  *event_msg)
{
  return 0;
}

/*static struct nla_policy event_fluid_pour_requested_pol
    [__DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_MAX] = {
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_CONTAINER] = {.type = NLA_U8},
        [DMC_EVENT_GENL_FLUID_POUR_REQUESTED_ATTR_AMOUNT]    = {.type = NLA_U8},
};*/

int dmc_netlink_unmarshal_event_fluid_pour_requested(
    struct dmc_event_fluid_pour_requested *event,
    struct dmc_netlink_event_msg          *event_msg)
{
  // Unmarshal data
  event->container = *(u8 *)nla_data(
      event_msg->attrs[DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_CONTAINER]);
  event->amount = *(u8 *)nla_data(
      event_msg->attrs[DMC_GENL_EVENT_FLUID_POUR_REQUESTED_ATTR_AMOUNT]);

  return 0;
}

int dmc_netlink_unmarshal_machine_ok(struct dmc_event_machine_ok  *event,
                                     struct dmc_netlink_event_msg *event_msg)
{
  // Unmarshal data
  return 0;
}

int dmc_netlink_unmarshal_event_debug(struct dmc_event_debug       *event,
                                      struct dmc_netlink_event_msg *event_msg)
{
  // Unmarshal data
  event->event_type =
      *(u8 *)nla_data(event_msg->attrs[DMC_GENL_EVENT_DEBUG_ATTR_EVENT_TYPE]);
  event->data =
      *(u8 *)nla_data(event_msg->attrs[DMC_GENL_EVENT_DEBUG_ATTR_DATA]);

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
                                   struct dmc_base_event        *base)
{
  int err;
  err = nla_put_u8(event_msg->buff, DMC_GENL_EVENT_BASE_ATTR_TYPE,
                   (u8)base->type);
  if (err != 0) return err;

  return 0;
}

int dmc_netlink_marshal_event_container_weight_measured(
    struct dmc_netlink_event_msg               *event_msg,
    struct dmc_event_container_weight_measured *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0) return err;

  // - MARK: Marshal event specific fields

  // Container
  err = nla_put_u8(event_msg->buff,
                   DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_CONTAINER,
                   event->container);
  if (err != 0) return err;

  // Weight
  err = nla_put_s16(event_msg->buff,
                    DMC_GENL_EVENT_CONTAINER_WEIGHT_MEASURED_ATTR_WEIGHT,
                    event->weight);
  if (err != 0) return err;

  return 0;
}

int dmc_netlink_marshal_event_out_of_order(
    struct dmc_netlink_event_msg  *event_msg,
    struct dmc_event_out_of_order *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0) return err;

  // - MARK: Marshal event specific fields

  // Message
  err =
      nla_put_string(event_msg->buff, DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_MESSAGE,
                     event->message);
  if (err != 0) return err;

  // Reason
  err = nla_put_u8(event_msg->buff, DMC_GENL_EVENT_OUT_OF_ORDER_ATTR_REASON,
                   event->reason);
  if (err != 0) return err;

  return 0;
}

int dmc_genl_marshal_event_user_confirm(struct dmc_netlink_event_msg *event_msg,
                                        struct dmc_event_user_confirm *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0) return err;

  return 0;
}

int dmc_genl_marshal_event_machine_ok(struct dmc_netlink_event_msg *event_msg,
                                      struct dmc_event_machine_ok  *event)
{
  int err;

  // Marshal base event
  err = dmc_netlink_marshal_base_event(event_msg, event->base);
  if (err != 0) return err;

  return 0;
}