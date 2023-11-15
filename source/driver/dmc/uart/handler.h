#ifndef DMC_UART_HANDLER_H
#define DMC_UART_HANDLER_H

#include <linux/types.h>

#include "../util.h"

struct dmc_uart_handler
{
  /**
   * @brief GPIO pin for transmitting UART communication (TX)
   */
  unsigned int gpio_tx;

  /**
   * @brief GPIO pin for receiving UART communication (RX)
   */
  unsigned int gpio_rx;

  /**
   * @brief Interrupt irq value. Set in dmc_uart_register.
   */
  int irq_rx;

  /**
   * @brief Function pointer to call when UART receives a byte
   */
  int (*on_byte_recv)(u8 data);
};

/**
 * @brief Registers the necessary resources for the uart to function
 */
int dmc_uart_register(struct dmc_uart_handler *uart);

/**
 * @brief Unregisters uart resources
 */
int dmc_uart_unregister(struct dmc_uart_handler *uart);

/**
 * @brief Starts the receiving sequence for a reading byte from the RX gpio,
 * using the configuration given in the dmc_uart struct. Usually, this should
 * be called when start bit is receiving, which in general should be when the
 * interrupt triggers
 */
int dmc_uart_start_recv(struct dmc_uart_handler *uart);

#endif // DMC_UART_HANDLER_H