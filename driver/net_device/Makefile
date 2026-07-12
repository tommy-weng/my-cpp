KVERS = $(shell uname -r)

obj-m := net_device.o

all:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) clean
