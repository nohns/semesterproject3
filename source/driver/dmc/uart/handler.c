#include "handler.h"

#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/serdev.h>

/* Declate the probe and remove functions */
static int  dmc_serdev_probe(struct serdev_device *serdev);
static void dmc_serdev_remove(struct serdev_device *serdev);

static struct of_device_id dmc_serdev_ids[] = {{
                                                   .compatible = "prj3,dmcdev",
                                               },
                                               {/* sentinel */}};
MODULE_DEVICE_TABLE(of, dmc_serdev_ids);

static struct serdev_device_driver dmc_serdev_driver = {
    .probe  = dmc_serdev_probe,
    .remove = dmc_serdev_remove,
    .driver =
        {
            .name           = "dmc-drier",
            .of_match_table = dmc_serdev_ids,
        },
};

/**
 * @brief Callback is called whenever a character is received
 */
static int dmc_serdev_recv(struct serdev_device *serdev,
                           const unsigned char *buffer, size_t size)
{
  printk("serdev_echo - Received %ld bytes with \"%s\"\n", size, buffer);
  return serdev_device_write_buf(serdev, buffer, size);
}

static const struct serdev_device_ops dmc_serdev_ops = {
    .receive_buf = dmc_serdev_recv,
};

/**
 * @brief This function is called on loading the driver
 */
static int dmc_serdev_probe(struct serdev_device *serdev)
{
  int status;
  printk("serdev_echo - Now I am in the probe function!\n");

  serdev_device_set_client_ops(serdev, &dmc_serdev_ops);
  status = serdev_device_open(serdev);
  if (status)
  {
    printk("serdev_echo - Error opening serial port!\n");
    return -status;
  }

  serdev_device_set_baudrate(serdev, 9600);
  serdev_device_set_flow_control(serdev, false);
  serdev_device_set_parity(serdev, SERDEV_PARITY_NONE);

  status = serdev_device_write_buf(
      serdev, "Type something: ", sizeof("Type something: "));
  printk("serdev_echo - Wrote %d bytes.\n", status);

  return 0;
}

/**
 * @brief This function is called on unloading the driver
 */
static void dmc_serdev_remove(struct serdev_device *serdev)
{
  printk("serdev_echo - Now I am in the remove function\n");
  serdev_device_close(serdev);
}

/**
 * @brief Registers the necessary resources for the uart to function
 */
int dmc_uart_handler_register(struct dmc_uart_handler *uart)
{
  if (serdev_device_driver_register(&dmc_serdev_driver))
  {
    printk("serdev_echo - Error! Could not load driver\n");
    return -1;
  }

  // Success!
  DMC_D("serdev_echo - Driver loaded successfully\n");
  return 0;
}

int dmc_uart_handler_unregister(struct dmc_uart_handler *uart)
{
  serdev_device_driver_unregister(&dmc_serdev_driver);
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
