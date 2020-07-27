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
static dev_t rpr0521_devicenumber;
static struct cdev c_dev;
static struct class *cl;
static char c[256];
static int  message_length;

const char init_buffer[2] = {0x40,0x80};
const char mode_buffer[2] = {0x41,0x85};

char data[10];


/** file operations of this driver */
static int open_rpr0521_driver(struct inode *i, struct file *f)
{
//printk(KERN_INFO "device open\n");
return 0;
}      


static int release_rpr0521_driver(struct inode *i, struct file *f)
{
//printk(KERN_INFO "device released\n");
return 0;
}      

static ssize_t read_rpr0521_driver(struct file *f, char __user *buf, size_t len, loff_t *off)
{


}

static ssize_t write_rpr0521_driver(struct file *f, char __user *buf, size_t len, loff_t *off)
{


}

/** structure defines for device info */
static struct i2c_device_id  rpr0521_id_table[]={
	{DEVICE_NAME,0},
	{}
};


MODULE_DEVICE_TABLE(i2c,rpr0521_id_table);

static struct i2c_driver rpr0521_driver = {
	.driver = {
		.name = DEVICE_NAME,
	},
	.id_table = rpr0521_id_table,
	.probe = rpr0521_probe,
	.remove = rpr0521_remove,
};


static int __init initchardriver(void)
{

int ret;
struct device *dev_ret;
printk(KERN_INFO "rpr0521_chardriver registred\n");
if( (ret = alloc_chrdev_region(&first, 0, 1, "rpr0521_chardriver_lkm")) <0  )
	{
        return ret;
	}

if(IS_ERR(cl = class_create(THIS_MODULE,"rpr0521_chardriver_class")))
	{
	unregister_chrdev_region(first, 1);
        return PTR_ERR(cl);
	}

if(IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "rpr0521_chardriver_null")))
	{
	class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return PTR_ERR(dev_ret);
	}

cdev_init(&c_dev,&fops_chardriver);
if( (ret=cdev_add(&c_dev, first, 1 )) <0 )
	{
	device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return ret;	
	}	
printk(KERN_INFO "<MAJOR,MINOR> == <%d,%d>\n", MAJOR(first), MINOR(first));
return 0;

}


/** driver deregistration */
static void __exit exitchardriver(void)
{
cdev_del(&c_dev);
device_destroy(cl, first);
class_destroy(cl);
unregister_chrdev_region(first,1);
printk(KERN_INFO "chardriver_lkm unregistered\n");
}



module_init(initchardriver);
module_exit(exitchardriver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayush Jain - The_RAM_raider");
MODULE_DESCRIPTION("character driver test1");	
