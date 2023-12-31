#ifndef DMC_EVENT_H
#define DMC_EVENT_H

#include <linux/types.h>

/**
 * @brief Enum type describing what kind of event we are dealing with
 */
enum dmc_event_type
{
  DMC_EVENT_TYPE_UNDEFINED = 0,

  /* ##################### */
  /*   Event type values   */
  /* ##################### */

  /**
   * @brief See struct dmc_event_out_of_order
   */
  DMC_EVENT_TYPE_OUT_OF_ORDER = 1,

  /**
   * @brief See struct dmc_event_container_volume_measured
   */
  DMC_EVENT_TYPE_CONTAINER_VOLUME_MEASURED = 2,

  /**
   * @brief See struct dmc_event_container_volume_measured
   */
  DMC_EVENT_TYPE_USER_CONFIRM = 3,

  /**
   * @brief See struct dmc_event_fluid_pour_requested
   */
  DMC_EVENT_TYPE_FLUID_POUR_REQUESTED = 4,

  /**
   * @brief See struct dmc_event_machine_ok
   */
  DMC_EVENT_TYPE_MACHINE_OK = 5,

  /**
   * @brief See struct dmc_event_debug
   */
  DMC_EVENT_TYPE_DEBUG = 6,

  /* ##################### */

  // Max event type
  __DMC_EVENT_TYPE_MAX
};

/**
 * @brief Top-level event metadata. Should not be used by consumers
 */
struct dmc_base_event
{
  enum dmc_event_type type;
};

/**
 * @brief Validate that base event is correctly formed
 * @returns Negative value on error and 0 on success
 */
int dmc_validate_base_event(struct dmc_base_event *base);

/**
 * @brief Event declaring machine is out of order with a text message for the
 * user to see on either touchscreen UI.
 *
 * Direction: PSoC -> RPi
 */
struct dmc_event_out_of_order
{
  // Top-level event metadata
  struct dmc_base_event *base;

  /* ##################### */
  /* Event specific fields */
  /* ##################### */

  /**
   * @brief Message to display to user. Can take the form of any of the
   * constants defined in out_of_order.h Null charater terminated.
   */
  char *message;

  /**
   * @brief The reason code, which the message was derived from. See enum
   * dmc_packet_out_of_order_reason for what the codes mean.
   */
  uint8_t reason;
};

/**
 * @brief Validate that base event is correctly formed
 * @returns Negative value on error and 0 on success
 */
int dmc_validate_event_out_of_order(struct dmc_event_out_of_order *event);

/**
 * @brief Event declaring that a new weight measurement has been made.
 *
 * Direction: PSoC -> RPi
 */
struct dmc_event_container_volume_measured
{
  // Top-level event metadata
  struct dmc_base_event *base;

  /**
   * @brief The container the measurement was from. Ranging from 0-2
   */
  uint8_t container;

  /**
   * @brief Volume measured in centiliters
   */
  uint8_t volume;
};

/**
 * @brief Event declaring that a new weight measurement.
 *
 * Direction: RPi -> PSoC
 */
struct dmc_event_user_confirm
{
  // Top-level event metadata
  struct dmc_base_event *base;
};

/**
 * @brief Event declaring that the machine should start to pour fluid.
 *
 * Direction: RPi -> PSoC
 */
struct dmc_event_fluid_pour_requested
{
  // Top-level event metadata
  struct dmc_base_event *base;

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
 * @brief Event for telling the machine that it is ok
 */
struct dmc_event_machine_ok
{
  struct dmc_base_event *base;
};

/**
 * @brief Event for debugging purposes
 */
struct dmc_event_debug
{
  struct dmc_base_event *base;

  /**
   * @brief The sample event to publish to netlink
   */
  enum dmc_event_type event_type;

  /**
   * @brief The sample event to publish to netlink
   */
  uint8_t data;
};

#endif // DMC_EVENT_H