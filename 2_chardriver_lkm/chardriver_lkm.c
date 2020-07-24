/** kernel headers */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

/** global variable declaration */
static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static char c[256];
static int  message_length;



/** file operations of this driver */
static int open_chardriver(struct inode *i, struct file *f)
{
return 0;
}      

static int release_chardriver(struct inode *i, struct file *f)
{
return 0;
}      

static ssize_t read_chardriver(struct file *f, char __user *buf, size_t len, loff_t *off)
{
if (copy_to_user(buf, &c, message_length) != 0)
	return -EFAULT;
else
        {
	return 0;
	}
}

static ssize_t write_chardriver(struct file *f, const char __user *buf, size_t len, loff_t *off)
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

/** structure file_operations */
static struct file_operations fops_chardriver=
{
.owner=THIS_MODULE,
.open=open_chardriver,
.release=release_chardriver,
.read=read_chardriver,
.write=write_chardriver
};

/**
*1.driver registration.
*2.a.file operations defined first, for vfs to pass operations to driver.
*2.b.device class created using cdev_init. 
*/


/** driver registration */
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

