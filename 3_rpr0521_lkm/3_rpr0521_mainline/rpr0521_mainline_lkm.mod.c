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
	{ 0xad730880, __VMLINUX_SYMBOL_STR(iio_read_const_attr) },
	{ 0xbba5df28, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_predisable) },
	{ 0x39285142, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_postenable) },
	{ 0x925de368, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x2ecd24b1, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xa152f50e, __VMLINUX_SYMBOL_STR(regcache_sync) },
	{ 0x7aeace6e, __VMLINUX_SYMBOL_STR(iio_device_release_direct_mode) },
	{ 0x1d3c3103, __VMLINUX_SYMBOL_STR(iio_device_claim_direct_mode) },
	{ 0x3e95b87, __VMLINUX_SYMBOL_STR(__pm_runtime_suspend) },
	{ 0x526c3a6c, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x897559f8, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0xe1f7f528, __VMLINUX_SYMBOL_STR(regmap_raw_write) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xae29b17d, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x498ccda, __VMLINUX_SYMBOL_STR(devm_iio_triggered_buffer_setup) },
	{ 0xf8a79a4b, __VMLINUX_SYMBOL_STR(devm_iio_trigger_register) },
	{ 0x4e915c79, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0x22276625, __VMLINUX_SYMBOL_STR(devm_iio_trigger_alloc) },
	{ 0xb5dfbeef, __VMLINUX_SYMBOL_STR(__pm_runtime_use_autosuspend) },
	{ 0x37198bb8, __VMLINUX_SYMBOL_STR(pm_runtime_set_autosuspend_delay) },
	{ 0x95b2654d, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x2aee63f4, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x99b8405, __VMLINUX_SYMBOL_STR(__devm_regmap_init_i2c) },
	{ 0xb303d81a, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0xa7134360, __VMLINUX_SYMBOL_STR(__pm_runtime_set_status) },
	{ 0x9658bb46, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0xbfce3a84, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0xe4ca3b4f, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8e0ab212, __VMLINUX_SYMBOL_STR(regcache_mark_dirty) },
	{ 0xfd16e532, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xbcd605f3, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0x8f9280a0, __VMLINUX_SYMBOL_STR(regmap_update_bits_base) },
	{ 0x65cd9129, __VMLINUX_SYMBOL_STR(iio_trigger_poll_chained) },
	{ 0x4bbb8425, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xe33155f2, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x3d8e36b4, __VMLINUX_SYMBOL_STR(iio_trigger_notify_done) },
	{ 0x550e3bd1, __VMLINUX_SYMBOL_STR(iio_push_to_buffers) },
	{ 0xab9053c3, __VMLINUX_SYMBOL_STR(regmap_bulk_read) },
	{ 0x8f678b07, __VMLINUX_SYMBOL_STR(__stack_chk_guard) },
	{ 0xf751a430, __VMLINUX_SYMBOL_STR(iio_get_time_ns) },
	{ 0xb832ffe3, __VMLINUX_SYMBOL_STR(iio_trigger_using_own) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:rpr0521");
MODULE_ALIAS("acpi*:RPR0521:*");
