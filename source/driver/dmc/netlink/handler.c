#include "handler.h"

#include "../event.h"
#include "attr.h"
#include "constants.h"
#include "message.h"
#include "policy.h"

// Keeps track of generic netlink commands
enum dmc_genl_cmds
{
  DMC_GENL_CMD_UNSPECIFIED,
  DMC_GENL_CMD_RAISE_EVENT,
  __DMC_GENL_CMD_MAX,
};

// The current handler registered with the driver
static const struct dmc_netlink_handler *curr_handler;
static struct genl_family                genl_fam;

/**
 * @brief Handle raise event command. Propagates the event to
 */
static int dmc_driver_raise_event_doit(struct sk_buff   *skb,
                                       struct genl_info *info)
{
  int err;

  pr_notice("dmc_driver: received event from netlink\n");

  /* send a message back*/
  /* allocate some memory, since the size is not yet known use NLMSG_GOODSIZE*/
  struct sk_buff *reply = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
  if (reply == NULL) return -ENOMEM;

  /* start the message */
  void *msg_head =
      genlmsg_put_reply(reply, info, &genl_fam, 0, info->genlhdr->cmd);
  if (msg_head == NULL)
  {
    return -ENOMEM;
  }
  /* finalize the message */
  genlmsg_end(reply, msg_head);

  /* send the message back */
  if (0 != genlmsg_reply(reply, info)) return -EINVAL;

  // Call the event handler
  struct dmc_netlink_event_msg event_msg = {
      .buff     = skb,
      .attrs    = info->attrs,
      .genl_hdr = info->genlhdr,
  };

  // Unmarshal base event
  struct dmc_base_event base;
  err = dmc_netlink_unmarshal_base_event(&base, &event_msg);
  if (err != 0)
  {
    pr_err("dmc_driver: received malformed base event from netlink\n");
    return err;
  };

  // Validate base event
  err = dmc_validate_base_event(&base);
  if (err != 0)
  {
    pr_err("dmc_driver: failed validation of base event from netlink\n");
    return err;
  }

  err = curr_handler->on_event_recv(&base, &event_msg);
  if (err != 0)
  {
    pr_err("dmc_driver: failed handling event from netlink\n");
    return err;
  }

  return 0;
}

static const struct genl_ops genl_ops[__DMC_GENL_CMD_MAX - 1] = {
    {.cmd    = DMC_GENL_CMD_RAISE_EVENT,
     .doit   = dmc_driver_raise_event_doit,
     .policy = dmc_genl_event_pol},
};

enum dmc_genl_multicast_groups
{
  DMC_GENL_MULTICAST_GROUP_EVENT = 0,
  __DMC_GENL_MULTICAST_GROUP_MAX,
};

static const struct genl_multicast_group
    genl_mcgrps[__DMC_GENL_MULTICAST_GROUP_MAX] = {
        [DMC_GENL_MULTICAST_GROUP_EVENT] =
            {
                .name = DMC_GENL_MULTICAST_GROUP_NAME,
            },
};

// Define Generic Netlink family
static struct genl_family genl_fam = {
    .name     = DMC_GENL_FAMILY_NAME,
    .version  = DMC_GENL_VERSION,
    .maxattr  = __DMC_GENL_EVENT_ATTR_MAX,
    .ops      = genl_ops,
    .module   = THIS_MODULE,
    .n_ops    = ARRAY_SIZE(genl_ops),
    .mcgrps   = genl_mcgrps,
    .n_mcgrps = ARRAY_SIZE(genl_mcgrps),
};

int dmc_register_netlink_handler(struct dmc_netlink_handler *handler)
{
  int err;

  // Set current handler
  curr_handler = handler;

  // Register generic netlink family in kernel
  err = genl_register_family(&genl_fam);
  if (err != 0)
  {
    pr_crit("dmc_driver: failed to register generic netlink family, err = %d\n",
            err);
    return err;
  }

  // Success
  handler->genl_fam = &genl_fam;
  return 0;
}

void dmc_unregister_netlink_handler(struct dmc_netlink_handler *handler)
{
  handler->genl_fam = NULL;
  genl_unregister_family(&genl_fam);
  curr_handler = NULL;
}

int dmc_netlink_publish_event(const struct dmc_netlink_handler *handler,
                              struct dmc_netlink_event_msg     *event_msg)
{
  int err = 0;

  // If event_msg has not yet been prepared. User should call
  // dmc_netlink_prepare_event beforehand
  if (event_msg->genl_hdr == NULL) return -EINVAL;

  // If handler is the current, then return bad address error
  // if (curr_handler == handler) return -EFAULT;

  // Make sure the message containing the event is finalized
  genlmsg_end(event_msg->buff, event_msg->genl_hdr);

  // Send it over multicast to the event multicast group
  err = genlmsg_multicast(&genl_fam, event_msg->buff, 0,
                          DMC_GENL_MULTICAST_GROUP_EVENT, GFP_KERNEL);
  if (err == -ESRCH)
  {
    pr_warn(
        "dmc_driver: multicast message sent, but nobody was listening...\n");
  }
  else if (err)
  {
    pr_err("dmc_driver: failed to send multicast genl message\n");
  }
  else
  {
    pr_info("dmc_driver: multicast message sent\n");
  }

  return err;
}

int dmc_netlink_prepare_event(struct dmc_netlink_event_msg *event_msg,
                              enum dmc_event_type           type)
{
  void *hdr;

  // Allocate message buffer
  struct sk_buff *event_buf = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
  if (unlikely(!event_buf))
  {
    pr_err("dmc_driver: failed to allocate memory for genl message\n");
    return -ENOMEM;
  }

  // Prepare by putting the generic netlink header into event buffer
  hdr = genlmsg_put(event_buf, 0, DMC_GENL_MULTICAST_GROUP_EVENT, &genl_fam, 0,
                    DMC_GENL_CMD_RAISE_EVENT);
  if (!hdr)
  {
    pr_err("dmc_driver: failed to allocate memory for genl header\n");
    nlmsg_free(event_buf);
    return -ENOMEM;
  }

  // Success! Set the pointers of the event message
  event_msg->type     = type;
  event_msg->buff     = event_buf;
  event_msg->genl_hdr = hdr;
  return 0;
}
