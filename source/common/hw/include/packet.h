#ifndef DMC_PACKET_H
#define DMC_PACKET_H

#include "base_packet.h"

#ifdef MODULE
#include <linux/types.h>
#else
#include <stdint.h>
#endif

/**
 * @brief Reason codes for why the machine is out of order
 */
enum dmc_packet_out_of_order_reason
{
  /**
   * @brief An unknown error has occured
   */
  DMC_PACKET_OUT_OF_ORDER_REASON_UNKNOWN = 0,

  /**
   * @brief The machine detected that a fluid container 1
   * was removed from the machine
   */
  DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_1_REMOVED = 1,

  /**
   * @brief The machine detected that a fluid container 2
   * was removed from the machine
   */
  DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_2_REMOVED = 2,

  /**
   * @brief The machine detected that a fluid container 3
   * was removed from the machine
   */
  DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_3_REMOVED = 3,
};

/**
 * @brief Packet declaring machine is out of order with a reason code. So errors
 * can be viewed on the touch screen UI.
 *
 * Direction: PSoC -> RPi
 */
struct dmc_packet_out_of_order
{
  /**
   * @brief The reason code for the machine to be out of order. See enum
   * dmc_packet_out_of_order_reason for what the codes mean
   */
  enum dmc_packet_out_of_order_reason reason;
};

/**
 * @brief Unmarshal data into out of order packet from base packet
 */
static int
dmc_packet_unmarshal_out_of_order(struct dmc_packet_out_of_order *packet,
                                  struct dmc_packet              *from)
{
  if (from->type != DMC_PACKET_OUT_OF_ORDER)
  {
    return -1;
  }

  uint8_t offset = 0;
  packet->reason = *(uint8_t *)(from->data + offset);

  return 0;
}

/**
 * @brief Marshal out of order packet struct into base packet
 */
static int
dmc_packet_marshal_out_of_order(struct dmc_packet              *to,
                                struct dmc_packet_out_of_order *packet)
{
  if (to == NULL)
  {
    to = dmc_packet_init(DMC_PACKET_OUT_OF_ORDER);
  }
  if (to->type != DMC_PACKET_OUT_OF_ORDER)
  {
    return -1;
  }

  uint8_t offset                  = 0;
  *(uint8_t *)(to->data + offset) = packet->reason;

  to->data_len = sizeof(packet->reason);
  return 0;
}

/**
 * @brief Packet declaring that a new weight measurement has been made.
 *
 * Direction: PSoC -> RPi
 */
struct dmc_packet_container_weight_measured
{
  /**
   * @brief The container the measurement was from. Ranging from 0-2
   */
  uint8_t container;

  /**
   * @brief Weight measured in grams
   */
  int16_t weight;
};

/**
 * @brief Unmarshal data into container weight measured packet from base packet
 */
static int dmc_packet_unmarshal_container_weight_measured(
    struct dmc_packet_container_weight_measured *packet,
    struct dmc_packet                           *from)
{
  if (from->type != DMC_PACKET_CONTAINER_WEIGHT_MEASURED)
  {
    return -1;
  }

  uint8_t offset    = 0;
  packet->container = *(uint8_t *)(from->data + offset);

  offset += sizeof(packet->container); // Move offset of previous data
  packet->weight = *(uint16_t *)(from->data + offset);

  return 0;
}

/**
 * @brief Marshal container weight measured packet struct into base packet
 */
static int dmc_packet_marshal_container_weight_measured(
    struct dmc_packet *to, struct dmc_packet_container_weight_measured *packet)
{
  if (to == NULL)
  {
    to = dmc_packet_init(DMC_PACKET_CONTAINER_WEIGHT_MEASURED);
  }
  if (to->type != DMC_PACKET_CONTAINER_WEIGHT_MEASURED)
  {
    return -1;
  }

  uint8_t offset                  = 0;
  *(uint8_t *)(to->data + offset) = packet->container;

  offset += sizeof(packet->container); // Move offset of previous data
  *(int16_t *)(to->data + offset) = packet->weight;

  to->data_len = sizeof(packet->container) + sizeof(packet->weight);
  return 0;
}

/**
 * @brief Packet declaring that a user has confirmed something on the
 * touchscreen
 *
 * Direction: RPi -> PSoC
 */
struct dmc_packet_user_confirm
{
};

/**
 * @brief Unmarshal data into user confirm packet from base packet
 */
static int
dmc_packet_unmarshal_user_confirm(struct dmc_packet_user_confirm *packet,
                                  struct dmc_packet              *from)
{
  if (from->type != DMC_PACKET_USER_CONFIRM)
  {
    return -1;
  }

  return 0;
}

/**
 * @brief Marshal user confirm packet struct into base packet
 */
static int
dmc_packet_marshal_user_confirm(struct dmc_packet              *to,
                                struct dmc_packet_user_confirm *packet)
{
  if (to == NULL)
  {
    to = dmc_packet_init(DMC_PACKET_USER_CONFIRM);
  }
  if (to->type != DMC_PACKET_USER_CONFIRM)
  {
    return -1;
  }

  return 0;
}

/**
 * @brief Packet declaring that machine is ok after being out of order
 *
 * Direction: RPi -> PSoC
 */
struct dmc_packet_machine_ok
{
};

/**
 * @brief Unmarshal data into machine ok packet from base packet
 */
static int dmc_packet_unmarshal_machine_ok(struct dmc_packet_machine_ok *packet,
                                           struct dmc_packet            *from)
{
  if (from->type != DMC_PACKET_MACHINE_OK)
  {
    return -1;
  }

  return 0;
}

/**
 * @brief Packet declaring that the machine should start to pour fluid.
 *
 * Direction: RPi -> PSoC
 */
struct dmc_packet_fluid_pour_requested
{
  /**
   * @brief The container to pour from. Ranging from 0-2
   */
  uint8_t container;

  /**
   * @brief Amount to pour in centiliters
   */
  uint8_t amount;
};

/**
 * @brief Unmarshal data into fluid pour requested packet from base packet
 */
static int dmc_packet_unmarshal_fluid_pour_requested(
    struct dmc_packet_fluid_pour_requested *packet, struct dmc_packet *from)
{
  if (from->type != DMC_PACKET_FLUID_POUR_REQUESTED)
  {
    return -1;
  }

  uint8_t offset    = 0;
  packet->container = *(uint8_t *)(from->data + offset);

  offset += sizeof(packet->container); // Move offset of previous data
  packet->amount = *(uint8_t *)(from->data + offset);

  return 0;
}

/**
 * @brief Marshal fluid pour requested packet struct into base packet
 */
static int dmc_packet_marshal_fluid_pour_requested(
    struct dmc_packet *to, struct dmc_packet_fluid_pour_requested *packet)
{
  if (to == NULL)
  {
    to = dmc_packet_init(DMC_PACKET_FLUID_POUR_REQUESTED);
  }
  if (to != NULL && to->type != DMC_PACKET_FLUID_POUR_REQUESTED)
  {
    return -1;
  }

  uint8_t offset                  = 0;
  *(uint8_t *)(to->data + offset) = packet->container;

  offset += sizeof(packet->container); // Move offset of previous data
  *(uint8_t *)(to->data + offset) = packet->amount;

  to->data_len = sizeof(packet->container) + sizeof(packet->amount);
  return 0;
}

#endif // DMC_PACKET_H