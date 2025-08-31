# DHT20温湿度传感器lxpanel插件 Makefile

CC = gcc
CFLAGS = -Wall -fPIC
LIBS = 

# 获取GTK和lxpanel的编译标志
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)
LXPANEL_CFLAGS = $(shell pkg-config --cflags lxpanel)
LXPANEL_LIBS = $(shell pkg-config --libs lxpanel)

# wiringPi标志 (手动指定)
WIRINGPI_CFLAGS = -I/usr/local/include
WIRINGPI_LIBS = -L/usr/local/lib -lwiringPi -lwiringPiDev -lm -lcrypt -lrt -lpthread

# 组合所有标志
ALL_CFLAGS = $(CFLAGS) $(GTK_CFLAGS) $(LXPANEL_CFLAGS) $(WIRINGPI_CFLAGS)
ALL_LIBS = $(GTK_LIBS) $(LXPANEL_LIBS) $(WIRINGPI_LIBS)

# 插件名称
PLUGIN_NAME = dht20_GLM
PLUGIN_FILE = $(PLUGIN_NAME).so

# 源文件
SRC = dht20_plugin.c

# 目标文件
OBJ = $(SRC:.c=.o)

# 默认目标
all: $(PLUGIN_FILE)

# 编译插件
$(PLUGIN_FILE): $(OBJ)
	$(CC) -shared -o $@ $< $(ALL_LIBS)

# 编译源文件
%.o: %.c
	$(CC) $(ALL_CFLAGS) -c $< -o $@

# 安装插件
install: $(PLUGIN_FILE)
	@echo "安装插件到 /usr/lib/aarch64-linux-gnu/lxpanel/plugins/"
	@sudo cp $(PLUGIN_FILE) /usr/lib/aarch64-linux-gnu/lxpanel/plugins/
	@echo "插件安装完成，请重启lxpanel使插件生效"

# 清理
clean:
	rm -f $(OBJ) $(PLUGIN_FILE)

.PHONY: all install clean