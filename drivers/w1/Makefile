#
# Makefile for the Dallas's 1-wire bus.
#
KERNEL_DIR = ~/zdyz/zdyz_kernel
MODULE_DIR = $(shell pwd)

obj-$(CONFIG_W1)	+= wire.o
wire-objs		:= w1.o w1_int.o w1_family.o w1_netlink.o w1_io.o

obj-y			+= masters/ slaves/

modules:
	make -C $(KERNEL_DIR) M=$(MODULE_DIR) modules

clean:
	rm *.o masters/*.o slaves/*.o