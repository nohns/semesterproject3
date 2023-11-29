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

static int (*dmc_on_byte_recv)(u8 data) = NULL;
static int curr_buf_idx                 = 0;
/**
 * @brief Callback is called whenever a character is received
 */
static int dmc_serdev_recv(struct serdev_device *serdev,
                           const unsigned char *buffer, size_t size)
{
  // pr_debug("dmc_driver: received bytes buffer of len %ld\n", size);
  //  for (int i = 0; i < size; i++)
  //{
  pr_debug("dmc_driver: received byte i=%d of value %d in seq of size %ld\n",
           curr_buf_idx, buffer[curr_buf_idx], size);
  if (dmc_on_byte_recv(buffer[curr_buf_idx++]) != 0)
  {
    pr_debug("dmc_driver: error handling byte\n");
    return -1;
  }
  //}

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
  pr_debug("dmc_driver: now I am in the probe function!\n");

  serdev_device_set_client_ops(serdev, &dmc_serdev_ops);
  status = serdev_device_open(serdev);
  if (status)
  {
    pr_debug("dmc_driver: error opening serial port!\n");
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
  dmc_on_byte_recv = on_byte_recv;

  // Success!
  return 0;
}

int dmc_uart_handler_unregister(void)
{
  serdev_device_driver_unregister(&dmc_serdev_driver);
  return 0;
}

int dmc_uart_handler_send_packet(struct dmc_packet *packet)
{
  int err;

  if (curr_serdev == NULL)
  {
    pr_debug("dmc_driver: error sending packet, no current serial device\n");
    return -1;
  }

  pr_debug("dmc_driver: sent packet type via serdev\n");
  pr_debug("dmc_driver: type ptr %d\n", packet->type);
  pr_debug("dmc_driver: data ptr %x\n", packet->data);
  pr_debug("dmc_driver: data len %d\n", packet->data_len);

  serdev_device_write_buf(curr_serdev, (unsigned char *)(&(packet->type)), 1);
  if (err)
  {
    pr_debug("dmc_driver: error sending packet type via serdev, err = %d\n",
             err);
    return -1;
  }

  serdev_device_write_buf(curr_serdev, packet->data, packet->data_len);
  if (err)
  {
    pr_debug("dmc_driver: error sending packet data via serdev, err = %d\n",
             err);
    return -1;
  }
  pr_debug("dmc_driver: sent packet data via serdev\n");

  return -ENOSYS;
}
