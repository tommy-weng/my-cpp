KDIR = /root/G2-ECC300/kernel/linux-5.10-origin

obj-m := net_device.o

all:
	make -C $(KDIR) M=$(PWD) modules CC=arm-linux-gnueabihf-gcc

clean:
	make -C $(KDIR) M=$(PWD) clean
