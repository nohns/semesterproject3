#include "event.h"

#include <asm-generic/errno-base.h>

int dmc_validate_base_event(struct dmc_base_event *base)
{
  // Check if type is really a valid event type
  if (base->type == 0 || base->type >= __DMC_EVENT_TYPE_MAX)
  {
    return -EINVAL;
  }

  return 0;
}

int dmc_validate_event_out_of_order(struct dmc_event_out_of_order *event)
{
  int err = dmc_validate_base_event(event->base);
  if (err != 0) return err;

  // - MARK: Validate event specific fields

  return 0;
}