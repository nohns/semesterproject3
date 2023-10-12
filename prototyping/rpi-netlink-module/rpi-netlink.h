#ifndef RPI_NETLINK_H
#define RPI_NETLINK_H

#define RPI_NETLINK_GENL_FAMILY_NAME "RPI_NETLINK_FAM"
#define RPI_NETLINK_GENL_VERSION 1
#define RPI_NETLINK_MULTICAST_GROUP_NAME "RPI_NETLINK_EVT"

// Keeps track of attributes
enum rpi_netlink_attrs
{
  RPI_NETLINK_ATTR_UNSPECIFIED = 0,
  RPI_NETLINK_ATTR_MSG         = 1,
  __RPI_NETLINK_ATTR_MAX       = 2,
};

#define RPI_NETLINK_ATTR_MAX (__RPI_NETLINK_ATTR_MAX - 1)

// Keeps track of generic netlink commands
enum rpi_netlink_genl_cmds
{
  RPI_NETLINK_GENL_CMD_UNSPECIFIED = 0,
  RPI_NETLINK_GENL_CMD_RAISE_EVENT = 1,
  RPI_NETLINK_GENL_EVENT           = 2,
  __RPI_NETLINK_GENL_CMD_MAX       = 3,
};

#define RPI_NETLINK_GENL_CMD_MAX (__RPI_NETLINK_GENL_CMD_MAX - 1)

#endif