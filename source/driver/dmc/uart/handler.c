#include "handler.h"

#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/wait.h>

DECLARE_WAIT_QUEUE_HEAD(dmc_uart_wq);

static irqreturn_t dmc_uart_handle_irq(int irq_number, void *dev_data)
{

  wake_up_interruptible(&dmc_uart_wq);

  return IRQ_HANDLED;
}

/**
 * @brief Registers the necessary resources for the uart to function
 */
int dmc_uart_handler_register(struct dmc_uart_handler *uart)
{
  int err;

  // Request RX and TX gpios
  err = gpio_request(uart->gpio_rx, "dmc_uart_rx");
  if (err != 0)
    ERRGOTO(fail_dmc_uart_reg_gpio_req_rx,
            "dmc_uart: failed gpio request for rx gpio %d\n", uart->gpio_rx);
  err = gpio_request(uart->gpio_tx, "dmc_uart_tx");
  if (err != 0)
    ERRGOTO(fail_dmc_uart_reg_gpio_req_tx,
            "dmc_uart: failed gpio request for tx gpio %d\n", uart->gpio_tx);

  // Set input and output for uart gpios
  err = gpio_direction_input(uart->gpio_rx);
  if (err != 0)
    ERRGOTO(fail_dmc_uart_reg_gpio_dir_input_rx,
            "dmc_uart: failed to set rx gpio %d to input\n", uart->gpio_rx);
  err = gpio_direction_output(uart->gpio_tx, 1);
  if (err != 0)
    ERRGOTO(fail_dmc_uart_reg_gpio_dir_output_tx,
            "dmc_uart: failed to set tx gpio %d to output\n", uart->gpio_tx);

  // Get IRQ number for uart rx gpio pin
  uart->irq_rx = gpio_to_irq(uart->gpio_rx);

  // Request interrupt for rx gpio pin
  err = request_irq(uart->irq_rx, dmc_uart_handle_irq, IRQF_TRIGGER_FALLING,
                    "dmc_uart_rx", NULL);
  if (err != 0) ERRGOTO(fail_dmc_uart_reg_irq_req, "Failed to \n");

  // Success
  return 0;

// Goto error handling...
fail_dmc_uart_reg_irq_req:
fail_dmc_uart_reg_gpio_dir_output_tx:
fail_dmc_uart_reg_gpio_dir_input_rx:
  gpio_free(uart->gpio_tx);

fail_dmc_uart_reg_gpio_req_tx:
  gpio_free(uart->gpio_rx);

fail_dmc_uart_reg_gpio_req_rx:
  return err;
}

int dmc_uart_handler_unregister(struct dmc_uart_handler *uart)
{
  free_irq(uart->irq_rx, NULL);
  gpio_free(uart->gpio_rx);
  gpio_free(uart->gpio_tx);
  return 0;
}

/**
 * @brief Starts the receiving sequence for a reading byte from the RX gpio,
 * using the configuration given in the dmc_uart struct. Usually, this should
 * be called when start bit is receiving, which in general should be when the
 * interrupt triggers
 */
int dmc_uart_handler_start_recv(struct dmc_uart_handler *uart) { return 0; }

int dmc_uart_handler_send_packet(struct dmc_uart_handler *uart,
                                 struct dmc_packet       *packet)
{
  // Return linux not implemented error
  return -ENOSYS;
}