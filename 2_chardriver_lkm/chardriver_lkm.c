/** kernel headers */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

/** global variable declaration */
static dev_t first;


/** driver registration */
static int __init chardriverinit(void)
{
int ret;
printk(KERN_INFO "chardev_lkm registred\n");
if( (ret = alloc_chrdev_region(&first, 0, 3, "chardev_lkm")) <0  )
	{
        return ret;
	}
printk(KERN_INFO "<MAJOR,MINOR> == <%d,%d>\n", MAJOR(first), MINOR(first));
return 0;
}


/** driver registration */
static void __exit chardriverexit(void)
{
unregister_chrdev_region(first,3);
printk(KERN_INFO "chardev_lkm unregistered\n");
}


module_init(chardriverinit);
module_exit(chardriverexit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayush Jain - The RAM raider");
MODULE_DESCRIPTION("character driver test1");	

