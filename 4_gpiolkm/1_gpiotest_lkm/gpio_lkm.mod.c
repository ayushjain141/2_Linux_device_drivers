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
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xc1514a3b, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xe04df39a, __VMLINUX_SYMBOL_STR(gpiod_unexport) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x3d0ddb5d, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0xf273bfc7, __VMLINUX_SYMBOL_STR(gpiod_set_debounce) },
	{ 0x2e7c4960, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0x27551b82, __VMLINUX_SYMBOL_STR(gpiod_export) },
	{ 0xba7fa7c1, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8d232dcf, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0x89df42aa, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0x53aa5f51, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7C615F5308835F528F723C3");
