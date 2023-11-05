#ifndef RPI_UART_H
#define RPI_UART_H

#include <linux/module.h>

#define UART_DRIVER_NAME "RPi AU UART driver"

// Adapted from:
// https://redweb.ece.au.dk/courses/projects/sw3hal/repository/2/revisions/master/entry/slides/init_exit_cdev.c
// (VPN)
#define ERRGOTO(label, ...)                                                    \
  {                                                                            \
    pr_err(__VA_ARGS__);                                                       \
    goto label;                                                                \
  }                                                                            \
  while (0)

#endif