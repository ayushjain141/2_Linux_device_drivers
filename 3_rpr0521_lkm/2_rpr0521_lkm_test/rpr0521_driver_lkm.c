/** linux kernel headers for i2c bus and algos */
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

/** linux kernel headers for character drivers and file I/O */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#include <linux/input.h>	/* BUS_I2C */
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/types.h>
#include <linux/pm.h>


/** global variable declaration */
static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static char c[256];
static int  message_length;
struct i2c_adapter *adap;

/** file operations of this driver */
static int open_rpr0521_chardriver(struct inode *i, struct file *f)
{
	return 0;
}      

static int release_rpr0521_chardriver(struct inode *i, struct file *f)
{
	return 0;
}      

static ssize_t read_rpr0521_chardriver(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	if (copy_to_user(buf, &c, message_length) != 0)
		return -EFAULT;
	else
	{
		return 0;
	}
}

static ssize_t write_rpr0521_chardriver(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	if (copy_from_user(&c, buf, len) != 0)
		return -EFAULT;
	else
	{
		printk(KERN_INFO "num of bytes = %d\n",len);		
		message_length=len;
		return len;
	}	       	
}


/** Character driver file operations declaration */
static struct file_operations fops_rpr0521_chardriver = {
	.owner=THIS_MODULE,
	.open=open_rpr0521_chardriver,
	.release=release_rpr0521_chardriver,
	.read=read_rpr0521_chardriver,
	.write=write_rpr0521_chardriver
};


/** i2c driver operation declaration */

/*
static int rpr0521_i2c_probe()
{
}
*/


/** i2c driver operation declaration */
static struct i2c_board_info rpr0521_i2cdriver_boardinfo[] = {
/*
	{
		.type = "rpr0521_driver_lkm",
		.addr = 0x38,  
	},
	{}
*/
{I2C_BOARD_INFO("rpr0521_driver_lkm",0x38)},
{}

};


static struct i2c_device_id rpr0521_i2cdriver_idtable[] = {
	{"rpr0521",0},
	{}
};

MODULE_DEVICE_TABLE(i2c, rpr0521_i2cdriver_idtable);

static struct i2c_driver rpr0521_i2cdriver = {
	.driver = {
		.name = "rpr0521_driver_lkm"
	},
	//.probe  = rpr0521_i2c_probe,
	//.remove = rpr0521_i2c_remove,
	.id_table = rpr0521_i2cdriver_idtable, 
};


/** driver registration */

/**
*1.driver registration.
*2.a.file operations defined above first  , for vfs to pass operations to driver.
*3.b.device class created using cdev_init. 
*/

static int __init initchardriver(void)
{
	int ret;
	struct device *dev_ret;
	printk(KERN_INFO "chardriver_lkm registred\n");
	if( (ret = alloc_chrdev_region(&first, 0, 1, "chardriver_lkm")) <0  )
	{
		return ret;
	}

	if(IS_ERR(cl = class_create(THIS_MODULE,"chardriver_class")))
	{
		unregister_chrdev_region(first, 1);
		return PTR_ERR(cl);
	}

	if(IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "chardriver_null")))
	{
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return PTR_ERR(dev_ret);
	}

	cdev_init(&c_dev,&fops_rpr0521_chardriver);
	if( (ret=cdev_add(&c_dev, first, 1 )) <0 )
	{
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return ret;	
	}	
	printk(KERN_INFO "<MAJOR,MINOR>==<%d,%d>\n", MAJOR(first), MINOR(first));
	
        //i2c_register_board_info(int busnum, struct i2c_board_info *info, unsigned len);
	//i2c_register_board_info(2, rpr0521_i2cdriver_boardinfo, ARRAY_SIZE(rpr0521_i2cdriver_boardinfo));
	//i2c_new_client_device(adap, &rpr0521_i2cdriver_boardinfo[0]);
	return  i2c_add_driver(&rpr0521_i2cdriver);

}


/** driver deregistration */
static void __exit exitchardriver(void)
{
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first,1);
	printk(KERN_INFO "chardriver_lkm unregistered\n");
	i2c_del_driver(&rpr0521_i2cdriver);
}

module_init(initchardriver);
module_exit(exitchardriver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayush Jain - The_RAM_raider");
MODULE_DESCRIPTION("character driver test1");

