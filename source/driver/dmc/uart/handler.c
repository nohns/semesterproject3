#include "handler.h"

#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/property.h>
#include <linux/serdev.h>
#include <linux/slab.h>

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

static int (*on_byte_recv)(u8 data) = NULL;

/**
 * @brief Callback is called whenever a character is received
 */
static int dmc_serdev_recv(struct serdev_device *serdev,
                           const unsigned char *buffer, size_t size)
{
  DMC_D("dmc_driver: received %ld bytes with \"%s\"\n");

  for (int i = 0; i < size; i++)
  {
    if (on_byte_recv(buffer[i]) != 0)
    {
      DMC_D(
          "dmc_driver: error handling byte %d of value %d in seq of size %ld\n",
          buffer[i], i, size);
      return -1;
    }
  }

  return 0;
}

static const struct serdev_device_ops dmc_serdev_ops = {
    .receive_buf = dmc_serdev_recv,
};

static struct serdev_device *curr_serdev = NULL;

/**
 * @brief This function is called on loading the driver
 */
static int dmc_serdev_probe(struct serdev_device *serdev)
{
  int status;
  DMC_D("dmc_driver: now I am in the probe function!\n");

  serdev_device_set_client_ops(serdev, &dmc_serdev_ops);
  status = serdev_device_open(serdev);
  if (status)
  {
    DMC_D("dmc_driver: error opening serial port!\n");
    return -status;
  }

  serdev_device_set_baudrate(serdev, 9600);
  serdev_device_set_flow_control(serdev, false);
  serdev_device_set_parity(serdev, SERDEV_PARITY_NONE);
  curr_serdev = serdev;

  return 0;
}

/**
 * @brief This function is called on unloading the driver
 */
static void dmc_serdev_remove(struct serdev_device *serdev)
{
  printk("serdev_echo - Now I am in the remove function\n");
  serdev_device_close(serdev);
  curr_serdev = NULL;
}

/**
 * @brief Registers the necessary resources for the uart to function
 */
int dmc_uart_handler_register(int (*on_byte_recv)(u8 data))
{
  int err;
  if ((err = serdev_device_driver_register(&dmc_serdev_driver)))
  {
    return -err;
  }

  // Success!
  return 0;
}

int dmc_uart_handler_unregister()
{
  serdev_device_driver_unregister(&dmc_serdev_driver);
  return 0;
}

int dmc_uart_handler_send_packet(struct dmc_packet *packet)
{
  if (curr_serdev == NULL)
  {
    DMC_D("dmc_driver: error sending packet, no current serial device\n");
    return -1;
  }

  // Return linux not implemented error
  size_t pcklen = packet->data_len + 1;
  u8    *arr    = (u8 *)kmalloc(pcklen, GFP_KERNEL);
  arr[0]        = packet->type;
  for (int i = 0; i < packet->data_len; i++)
  {
    arr[i + 1] = packet->data[i];
  }

  int err = serdev_device_write_buf(curr_serdev, arr, pcklen);
  kfree((void *)arr);
  if (err)
  {
    DMC_D("dmc_driver: error sending packet via serdev, err = %d\n", err);
    return -1;
  }

  return -ENOSYS;
}
