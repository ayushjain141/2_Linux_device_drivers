cmd_/root/1_workspace/2_device_drivers/1_hello_lkm/hello_lkm.ko := ld -EL -r  -T ./scripts/module-common.lds --build-id  -T ./arch/arm/kernel/module.lds -o /root/1_workspace/2_device_drivers/1_hello_lkm/hello_lkm.ko /root/1_workspace/2_device_drivers/1_hello_lkm/hello_lkm.o /root/1_workspace/2_device_drivers/1_hello_lkm/hello_lkm.mod.o ;  true
