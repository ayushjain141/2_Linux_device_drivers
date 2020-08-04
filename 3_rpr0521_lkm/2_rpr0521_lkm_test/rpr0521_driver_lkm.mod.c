#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa0a7cae5, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x925de368, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x71873fdc, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x19d060cb, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x2ecd24b1, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x11915b78, __VMLINUX_SYMBOL_STR(i2c_new_device) },
	{ 0x22186465, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0x37af6c70, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x52c7f37c, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x68ba5a9, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xb08f9e48, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xa08b248e, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x1327b810, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:rpr0521");
