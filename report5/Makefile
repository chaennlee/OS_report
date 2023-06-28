obj-m = mydrv.o

KERNEL_DIR = /lib/modules/$(shell uname -r)/build

default :
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) modules
	
clean :
	$(MAKE) -C $(KERNEL_DIR) M=$(shell pwd) clean

