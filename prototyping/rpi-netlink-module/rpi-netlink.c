#include <linux/module.h>
/*#include <net/genetlink.h>

#include "rpi-netlink.h"

// Socket for sending multicast events
struct sock *nl_mc_sock = NULL;

// Socket for receiving read commands
struct sock *nl_uc_sock = NULL;

// Forward declaration
static struct genl_family genl_fam;

// Validation for raise_event generic netlink command
static struct nla_policy raise_event_pol[RPI_NETLINK_ATTR_MAX + 1] = {
    [RPI_NETLINK_ATTR_MSG] = {.type = NLA_NUL_STRING},
};

// Multicast a string message
static int multicast_echo(const char *buf, size_t cnt)
{
  int   ret = 0;
  void *hdr;
  // Allocate message buffer
  struct sk_buff *skb = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);

  if (unlikely(!skb))
  {
    pr_err("failed to allocate memory for genl message\n");
    return -ENOMEM;
  }

  // Put the Generic Netlink header
  hdr = genlmsg_put(skb, 0, 0, &genl_fam, 0, RPI_NETLINK_GENL_EVENT);
  if (unlikely(!hdr))
  {
    pr_err("failed to allocate memory for genl header\n");
    nlmsg_free(skb);
    return -ENOMEM;
  }

  // And the message
  if ((ret = nla_put_string(skb, RPI_NETLINK_ATTR_MSG, buf)))
  {
    pr_err("unable to create message string\n");
    genlmsg_cancel(skb, hdr);
    nlmsg_free(skb);
    return ret;
  }

  // Finalize the message
  genlmsg_end(skb, hdr);

  // Send it over multicast to the 0-th mc group in our array.
  ret = genlmsg_multicast(&genl_fam, skb, 0, 0, GFP_KERNEL);
  if (ret == -ESRCH)
  {
    pr_warn("multicast message sent, but nobody was listening...\n");
  }
  else if (ret)
  {
    pr_err("failed to send multicast genl message\n");
  }
  else
  {
    pr_info("multicast message sent\n");
  }

  return ret;
}

// Handle raise event command
static int raise_event_doit(struct sk_buff *skb, struct genl_info *info)
{
  // Validate incoming attributes
  if (nla_validate(*info->attrs, RPI_NETLINK_ATTR_MAX, NLA_TYPE_MAX,
                   raise_event_pol, NULL))
  {
    pr_err("could not validate netlink attributes...\n");
    return -1;
  }

  // Check if the attribute is present and print it
  char  *str;
  size_t len;
  if (info->attrs[RPI_NETLINK_ATTR_MSG])
  {
    str = nla_data(info->attrs[RPI_NETLINK_ATTR_MSG]);
    len = nla_len(info->attrs[RPI_NETLINK_ATTR_MSG]);
    pr_info("message received: %s\n", str);
  }
  else
  {
    pr_info("empty message received\n");
  }

  multicast_echo(str, len);
  pr_info("event emitted\n");
  return 0;
}

// All commands available through netlink socket, using generic netlink and
// family
static struct genl_ops genl_ops[] = {
    {
        .cmd  = RPI_NETLINK_GENL_CMD_RAISE_EVENT,
        .doit = raise_event_doit,
    },
};

static const struct genl_multicast_group genl_mcgrps[] = {
    {.name = RPI_NETLINK_MULTICAST_GROUP_NAME},
};

// Generic Netlink family
static struct genl_family genl_fam = {
    .name     = RPI_NETLINK_GENL_FAMILY_NAME,
    .version  = RPI_NETLINK_GENL_VERSION,
    .maxattr  = RPI_NETLINK_ATTR_MAX,
    .ops      = genl_ops,
    .n_ops    = ARRAY_SIZE(genl_ops),
    .mcgrps   = genl_mcgrps,
    .n_mcgrps = ARRAY_SIZE(genl_mcgrps),
};
*/

static int __init rpi_netlink_init(void)
{
  pr_info("initializing rpi netlink module...\n");
  /*int ret = genl_register_family(&genl_fam);
  if (ret)
  {
    pr_crit("failed to register generic netlink family\n");
  }

  return ret;*/
  return 0;
}

static void __exit rpi_netlink_exit(void)
{
  /* if (genl_unregister_family(&genl_fam) != 0)
  {
    pr_crit("failed to unregister generic netlink family\n");
  }*/

  pr_info("removed rpi netlink module\n");
}

// Define metadata for module
MODULE_LICENSE("GPL");
MODULE_AUTHOR("PRJ3 group 12");
MODULE_DESCRIPTION("Loopback netlink driver experiment for communicating "
                   "between hardware driver and Web API");

// Set callbacks
module_init(rpi_netlink_init);
module_exit(rpi_netlink_exit);