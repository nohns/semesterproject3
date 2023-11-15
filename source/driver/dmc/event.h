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
   * @brief See dmc_event_out_of_order
   */
  DMC_EVENT_TYPE_OUT_OF_ORDER = 1,

  /**
   * @brief See dmc_event_container_weight_changed
   */
  DMC_EVENT_TYPE_CONTAINER_WEIGHT_MEASURED = 2,

  /**
   * @brief See dmc_event_container_weight_measured
   */
  DMC_EVENT_TYPE_USER_CONFIRM = 3,

  /**
   * @brief See dmc_event_pour_fluid
   */
  DMC_EVENT_TYPE_FLUID_POUR_REQUESTED = 4,

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
   * @brief Message to display to user. Null charater terminated.
   */
  char *f_msg;
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
struct dmc_event_container_weight_measured
{
  // Top-level event metadata
  struct dmc_base_event *base;

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

#endif // DMC_EVENT_H