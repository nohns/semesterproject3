#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/uaccess.h>

static int __init dm_hw_driver_init(void) { return 0; }

static void __exit dm_hw_driver_exit(void) {}

module_init(dm_hw_driver_init);
module_exit(dm_hw_driver_exit);