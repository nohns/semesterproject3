#ifndef DMC_CTRL_PACKET_HANDLER_H
#define DMC_CTRL_PACKET_HANDLER_H

#include "../netlink/handler.h"

#include "packet.h"

/**
 * @brief A struct defining the dependencies of the control packet handler
 */
struct dmc_ctrl_packet_handler
{
  struct dmc_netlink_handler *nl_handler;
};

/**
 * @brief Handles receiving an out of order packet from hardware.
 * @returns 0 on success, negative on failure
 */
int dmc_ctrl_on_packet_out_of_order(struct dmc_ctrl_packet_handler *pck_handler,
                                    struct dmc_packet_out_of_order *packet);

/**
 * @brief Handles receiving a container volume measured packet from hardware.
 * @returns 0 on success, negative on failure
 */
int dmc_ctrl_on_packet_container_volume_measured(
    struct dmc_ctrl_packet_handler              *pck_handler,
    struct dmc_packet_container_volume_measured *packet);

/**
 * @brief Handles receiving a machine ok packet from hardware.
 * @returns 0 on success, negative on failure
 */
int dmc_ctrl_on_packet_machine_ok(struct dmc_ctrl_packet_handler *pck_handler,
                                  struct dmc_packet_machine_ok   *packet);

#endif // DMC_CTRL_PACKET_HANDLER_H