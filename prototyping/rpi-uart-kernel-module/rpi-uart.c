#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/serial_core.h>
#include <linux/uaccess.h>

#include "rpi-uart.h"

static int rpi_uart_startup(struct uart_port *port)
{
  struct ktermios termios;

  /* Initialize termios structure */
  memset(&termios, 0, sizeof(termios));

  /* Set baud rate */
  termios.c_cflag = B9600;

  /* Set data bits */
  termios.c_cflag |= CS8; /* 8 data bits */

  /* Set stop bits */
  /* No need to set stop bits for 1 stop bit (default) */

  /* Set parity bits */
  /* No need to set parity for no parity (default) */

  /* Apply settings */
  uart_update_termios() uart_update_termios(port, &termios);

  return 0;
}

static void rpi_uart_start_tx(struct uart_port *port)
{
  struct circ_buf *xmit = &port->state->xmit;

  while (!uart_circ_empty(xmit))
  {
    /* Loopback: write the data back to the receive buffer */
    uart_insert_char(port, 0, 0, xmit->buf[xmit->tail], TTY_NORMAL);
    xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);

    /*Log the event */
    pr_info("Loopback: wrote %c to receive buffer\n", xmit->buf[xmit->tail]);
  }

  /* Wake up any reading process */
  tty_flip_buffer_push(port->state->port.tty);
}

static void rpi_uart_stop_tx(struct uart_port *port)
{
  /* Nothing to do here for a loopback */
}

static void rpi_uart_stop_rx(struct uart_port *port)
{
  /* Nothing to do here for a loopback */
}

static unsigned int rpi_uart_tx_empty(struct uart_port *port)
{
  /* For a loopback, the transmitter is always empty */
  return TIOCSER_TEMT;
}

static struct uart_ops rpi_uart_ops = {
    .startup  = rpi_uart_startup,
    .tx_empty = rpi_uart_tx_empty,
    .start_tx = rpi_uart_start_tx,
    .stop_tx  = rpi_uart_stop_tx,
    .stop_rx  = rpi_uart_stop_rx,
};

static struct uart_port rpi_uart_port = {
    .ops = &rpi_uart_ops, .flags = UPF_BOOT_AUTOCONF, .line = 0};

static struct uart_driver rpi_uart_driver = {
    .owner       = THIS_MODULE,
    .driver_name = UART_DRIVER_NAME,
    .major       = 0, // Get major number assigned by kernel
};

static int rpi_uart_probe(struct platform_device *pdev)
{
  rpi_uart_port.dev = &pdev->dev;
  return uart_add_one_port(&rpi_uart_driver, &rpi_uart_port);
}

static int rpi_uart_remove(struct platform_device *pdev)
{
  uart_remove_one_port(&rpi_uart_driver, &rpi_uart_port);
  return 0;
}

static struct platform_driver rpi_uart_platform_driver = {
    .probe  = rpi_uart_probe,
    .remove = rpi_uart_remove,
    .driver =
        {
            .name  = UART_DRIVER_NAME,
            .owner = THIS_MODULE,
        },
};

static int __init rpi_uart_init(void)
{
  int err;

  // Register native kernel uart driver, that controls serial comm with
  // external hardware
  err = uart_register_driver(&rpi_uart_driver);
  if (err)
    ERRGOTO(failed_reg_uart, "failed to register serial_core.h uart driver\n");

  pr_info("rpi uart driver godt major %d\n", rpi_uart_driver.major);

  // Register platform driver, which handles binding devices to this driver
  err = platform_driver_register(&rpi_uart_platform_driver);
  if (err)
    ERRGOTO(failed_reg_platform,
            "failed to register platfrom_device.h platform driver\n");

  return 0;

failed_reg_platform:
  uart_unregister_driver(&rpi_uart_driver);

failed_reg_uart:
  return err;
}

static void __exit rpi_uart_exit(void) {}

module_init(rpi_uart_init);
module_exit(rpi_uart_exit);