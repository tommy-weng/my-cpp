CC = gcc
CFLAGS = -Wall -fPIC $(shell pkg-config --cflags lxpanel gtk+-3.0)
LIBS = $(shell pkg-config --libs lxpanel gtk+-3.0) -lwiringPi
PLUGIN_NAME = dht20_lingma.so

all: $(PLUGIN_NAME)

$(PLUGIN_NAME): dht20_plugin.c
	$(CC) $(CFLAGS) -shared -o $@ $< $(LIBS)

install: $(PLUGIN_NAME)
	sudo install -m 755 $(PLUGIN_NAME) /usr/lib/aarch64-linux-gnu/lxpanel/plugins/

clean:
	rm -f $(PLUGIN_NAME)

.PHONY: all install clean