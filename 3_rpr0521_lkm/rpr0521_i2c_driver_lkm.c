/** i2c kernel headers taken from rpr0521 mainline kernel - https://github.com/torvalds/linux/blob/master/drivers/iio/light/rpr0521.c */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/regmap.h>
#include <linux/delay.h>
#include <linux/acpi.h>

#include <linux/iio/iio.h>
#include <linux/iio/buffer.h>
#include <linux/iio/trigger.h>
#include <linux/iio/trigger_consumer.h>
#include <linux/iio/triggered_buffer.h>
#include <linux/iio/sysfs.h>
#include <linux/pm_runtime.h>


/** these are for character driver functions an utilities - https://github.com/ayushjain141/2_Linux_device_drivers/blob/master/2_chardriver_lkm/chardriver_lkm.c  */
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>


/** Macro defines  */
#define DEVICE_NAME	"rpr0521"
#define ADDR		0x38 		

/** global variable declaration */
static dev_t rpr0521_majminnum;
static struct cdev c_dev;
static struct class *cl;
static char c[256];
static int  message_length;

const char init_buffer[2] = {0x40,0x80};
const char mode_buffer[2] = {0x41,0x85};

char data[10];

/** structure defines for device info */
static struct i2c_device_id  rpr0521_id_table[]={
	{DEVICE_NAME,0},
	{}
};

static int open_chardriver(struct inode *i, struct file *f)
{
printk(KERN_INFO "device open\n");
return 0;
}      

static int release_chardriver(struct inode *i, struct file *f)
{
printk(KERN_INFO "device released\n");
return 0;
}      



MODULE_DEVICE_TABLE(i2c,rpr0521_id_table);

static struct i2c_driver rpr0521_driver = {
	.driver = {
		.name=DEVICE_NAME,
	},
	.id_table = rpr0521_id_table,
	.probe = rpr0521_probe,
	.remove = rpr0521_remove,
};

