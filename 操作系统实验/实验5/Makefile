TARGET=procfs_example
KDIR :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
obj-m :=$(TARGET).o
default:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.order