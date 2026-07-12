KVERS = $(shell uname -r)

obj-m := helloworld.o
$(warning $(PWD))
all:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) clean
