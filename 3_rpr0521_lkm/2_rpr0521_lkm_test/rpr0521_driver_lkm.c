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

///======  taken from mpu6050 android  
//= https://android.googlesource.com/kernel/msm.git/+/android-msm-bullhead-3.10-marshmallow-dr-0/drivers/input/misc/mpu6050.c
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/pm_runtime.h>
#include <linux/gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/of_gpio.h>

/**sensor configuration data */
#define BUFFER_SIZE 10  
#define ADDR 0x38 	

char const init_buffer[2] = {0x40,0x80};
char const mode_buffer[2] = {0x41,0x85};
const char als_addr_buffer[1]={0x46};


/** global variable declaration */
static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static char c[256];
static int  message_length;

struct i2c_adapter *i2c_adap; 
struct i2c_client  *client; 

static char data_to_user[256];
static char data_from_user[256];

///////////////////////////////////////////////
/** file operations char driver */
///////////////////////////////////////////////

/** char driver operation definition */
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
	static int num_read_bytes=0;
	//num_read_bytes = len;
	i2c_master_recv(client, data_to_user ,2);			
	if (copy_to_user(buf, &data_to_user, 2) != 0)
		return -EFAULT;
	else
	{
		return 0;
	}
}

static ssize_t write_rpr0521_chardriver(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	static int num_write_bytes=0;
	num_write_bytes = len;
	if (copy_from_user(&data_from_user, buf, num_write_bytes) != 0)
		return -EFAULT;
	else
	{
		printk(KERN_INFO " num of commands to sensor = %d\n",len);	
		//message_length=len;
		i2c_master_send(client, data_from_user, len);
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


//////////////////////////////////////////////////////
/** i2c driver operation definition/declaration */
//////////////////////////////////////////////////////


/** i2c hardware declaration */
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

static const unsigned short normal_i2c[] = { ADDR, I2C_CLIENT_END };


/** i2c device id  declaration */
static struct i2c_device_id rpr0521_i2cdriver_idtable[] = {
	{"rpr0521",0},
	{}
};

MODULE_DEVICE_TABLE(i2c, rpr0521_i2cdriver_idtable);


/** i2c driver operation definition */


/** i2c driver declaration */
static struct i2c_driver rpr0521_i2cdriver = {
	.driver = {
		.name = "rpr0521_driver_lkm"
	},
	.id_table = rpr0521_i2cdriver_idtable, 
	//.probe  = rpr0521_i2c_probe,			to be checked later  
	//.remove = rpr0521_i2c_remove,			may not be used		  	
};


///////////////////////////////////////////////////
/** i2c and character driver registration */
///////////////////////////////////////////////////

/**
*1.driver registration.
*2.a.file operations defined above first  , for vfs to pass operations to driver.
*3.b.device class created using cdev_init. 
*/

static int __init initchardriver(void)
{
	/** char driver initialization  */
	int ret,ret2,ret_init_write;
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

	if(IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "chardriver_null")))  ///  chardriver_null appears in /dev/null
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

	/** i2c initialization */
	i2c_adap = i2c_get_adapter(2);	
	client = i2c_new_device(i2c_adap,&rpr0521_i2cdriver_boardinfo[0]);   //create new client
	ret2 = i2c_add_driver(&rpr0521_i2cdriver);
	
	/** i2c_smbus write sensor init commands */	
	if( (ret_init_write = i2c_master_send(client, init_buffer, 2 )) > 0 )
	{
	printk(KERN_INFO "sensor init success = %d  \n", ret_init_write);
	}	

	if( (ret_init_write = i2c_master_send(client, mode_buffer, 2 )) >  0 )
	{
	printk(KERN_INFO "sensor mode success = %d \n", ret_init_write);
	}	
	return ret2;

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

//module_i2c_driver(rpr0521_i2cdriver);   /// substitution of __init and __exit

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ayush Jain - The_RAM_raider");
MODULE_DESCRIPTION("character driver test1");

