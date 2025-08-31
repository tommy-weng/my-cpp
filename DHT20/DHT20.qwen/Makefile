# Makefile for DHT20 LXPanel plugin

# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -fPIC
CPPFLAGS = $(shell pkg-config --cflags lxpanel gtk+-3.0) -I/usr/include/lxpanel
LDFLAGS = $(shell pkg-config --libs lxpanel gtk+-3.0) -lwiringPi

# Plugin name
PLUGIN_NAME = dht20_qwen
PLUGIN_SO = $(PLUGIN_NAME).so

# Source files
SRCS = dht20_panel_plugin.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(PLUGIN_SO)

# Compile the plugin
$(PLUGIN_SO): $(OBJS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Install the plugin
install: $(PLUGIN_SO)
	sudo cp $(PLUGIN_SO) /usr/lib/aarch64-linux-gnu/lxpanel/plugins/

# Clean build files
clean:
	rm -f $(OBJS) $(PLUGIN_SO)

# Phony targets
.PHONY: all install clean