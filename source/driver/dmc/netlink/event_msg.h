#ifndef DMC_NETLINK_EVENT_MSG_H
#define DMC_NETLINK_EVENT_MSG_H

#include <net/genetlink.h>

/**
 * @brief Wrapper struct for holding relevant information about a generic
 * netlink message containing an event. Only interact / mutate this with
 * relevant netlink functions specified in this header file.
 */
struct dmc_netlink_event_msg
{
  /**
   * @brief Type of event that this message contains
  */
  enum dmc_event_type type;

  /**
   * @brief Ptr to underlying buffer for holding message representation of
   * event, that gets broadcasts
   */
  struct sk_buff *buff;

  /**
   * @brief Ptr to the parsed generic netlink message attributes in the buffer
   * above. This is only available on receive events, and will be NULL anywhere
   * else.
   */
  struct nlattr **attrs;

  /**
   * @brief Ptr to the memory location of the generic netlink header in the
   * buffer above
   */
  void *genl_hdr;
};

#endif // DMC_NETLINK_EVENT_MSG_H
