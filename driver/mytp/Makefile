
obj-m += mytp.o

KERNELDIR ?= /home/wanghan/work/cm895/d6/arm11/out/target/product/ugglite/obj/KERNEL_OBJ/
PWD ?= $(shell pwd)
ARCH = arm64
CROSS_COMPILE=/home/wanghan/work/cm895/d6/arm11/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld 
CFLAGS_MODULE=-fno-pic

.PHONY: modules clean
modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR) M=$(PWD) modules
	perl /home/wanghan/source/kernel/scripts/sign-file sha512 $(PWD)/signing_key.priv $(PWD)/signing_key.x509 mytp.ko
clean:
	rm *.o *.mod.c *.order *.symvers *.ko
