#ifndef DMC_UTIL_H
#define DMC_UTIL_H

#include "../dmc_driver.h"

// Adapted from: init_exit_cdev.c (see SOURCES in the top of this file)
#define ERRGOTO(label, ...)                                                    \
  {                                                                            \
    pr_err(__VA_ARGS__);                                                       \
    goto label;                                                                \
  }                                                                            \
  while (0)

// Adapted from: init_exit_cdev.c (see SOURCES in the top of this file)
#define DMC_D(...)                                                             \
  {                                                                            \
    pr_debug(__VA_ARGS__);                                                     \
  }                                                                            \
  while (0)

#endif // DMC_UTIL_H