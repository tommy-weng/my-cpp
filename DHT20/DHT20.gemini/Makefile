# Makefile for DHT20 LXPanel plugin

# Plugin name
PLUGIN = dht20_gemini

# Compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC `pkg-config --cflags lxpanel gtk+-2.0 glib-2.0`
LDFLAGS = -shared `pkg-config --libs lxpanel gtk+-2.0 glib-2.0` -lwiringPi

# Source file
SRC = lxpanel-dht20.c

# Target shared object
TARGET = $(PLUGIN).so

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Install rule (requires root)
install: $(TARGET)
	sudo install -m 755 $(TARGET) /usr/lib/aarch64-linux-gnu/lxpanel/plugins/

# Clean rule
clean:
	rm -f $(TARGET)