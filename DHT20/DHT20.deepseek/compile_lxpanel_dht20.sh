#!/bin/sh
gcc -shared -fPIC -o lxpanel_dht20.so lxpanel_dht20.c \
    $(pkg-config --cflags --libs gtk+-3.0 lxpanel) \
    -lwiringPi
