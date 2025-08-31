#include <lxpanel/plugin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPiI2C.h>

#define DHT20_ADDR 0x38 // DHT20 I2C address

// Plugin private data
typedef struct {
    GtkWidget *label;
    int i2c_fd;
    guint timer_tag;
} Dht20Plugin;

// Periodically called function to update sensor data
static gboolean update_sensor_data(gpointer data) {
    Dht20Plugin *plugin = (Dht20Plugin *)data;
    char buffer[64];

    if (plugin->i2c_fd < 0) {
        snprintf(buffer, sizeof(buffer), "I2C Error");
        gtk_label_set_text(GTK_LABEL(plugin->label), buffer);
        return TRUE; // Keep timer running to allow for reconnection
    }

    // Trigger measurement
    unsigned char cmd[3] = {0xAC, 0x33, 0x00};
    if (write(plugin->i2c_fd, cmd, 3) != 3) {
        snprintf(buffer, sizeof(buffer), "Write Error");
        gtk_label_set_text(GTK_LABEL(plugin->label), buffer);
        return TRUE;
    }

    usleep(80000); // Wait for measurement

    // Read 7 bytes of data
    unsigned char sensor_data[7];
    if (read(plugin->i2c_fd, sensor_data, 7) != 7) {
        snprintf(buffer, sizeof(buffer), "Read Error");
        gtk_label_set_text(GTK_LABEL(plugin->label), buffer);
        return TRUE;
    }

    // Check status byte
    if (sensor_data[0] & 0x80) {
        // Sensor is busy, don't update, wait for next cycle
        return TRUE;
    }

    // Calculate humidity
    unsigned int raw_humidity = ((unsigned int)sensor_data[1] << 12) |
                                ((unsigned int)sensor_data[2] << 4) |
                                ((unsigned int)sensor_data[3] >> 4);
    float humidity = (float)raw_humidity * 100.0 / 1048576.0;

    // Calculate temperature
    unsigned int raw_temp = (((unsigned int)sensor_data[3] & 0x0F) << 16) |
                           ((unsigned int)sensor_data[4] << 8) |
                           (unsigned int)sensor_data[5];
    float temperature = (float)raw_temp * 200.0 / 1048576.0 - 50.0;

    snprintf(buffer, sizeof(buffer), "%.1f°C | %.1f%%", temperature, humidity);
    gtk_label_set_text(GTK_LABEL(plugin->label), buffer);

    return TRUE; // Return TRUE to keep the timer running
}

// Called when the plugin is destroyed
static void dht20_destructor(gpointer user_data) {
    Dht20Plugin *plugin = (Dht20Plugin *)user_data;
    if (plugin->timer_tag > 0) {
        g_source_remove(plugin->timer_tag);
    }
    if (plugin->i2c_fd >= 0) {
        close(plugin->i2c_fd);
    }
    g_free(plugin);
}

// Called when the plugin is constructed
static GtkWidget *dht20_constructor(LXPanel *panel, config_setting_t *settings) {
    Dht20Plugin *plugin = g_new0(Dht20Plugin, 1);

    plugin->i2c_fd = wiringPiI2CSetup(DHT20_ADDR);

    // Create a label widget
    plugin->label = gtk_label_new("Loading...");
    gtk_widget_show(plugin->label);

    // Create a container for the label
    GtkWidget *container = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(container), plugin->label);

    // Set plugin properties
    lxpanel_plugin_set_data(container, plugin, dht20_destructor);
    
    // Start a timer to update the data every 2 seconds (2000 ms)
    plugin->timer_tag = g_timeout_add(2000, update_sensor_data, plugin);
    
    // Initial update
    update_sensor_data(plugin);

    return container;
}

// 插件初始化结构体
FM_DEFINE_MODULE(lxpanel_gtk, dht20_gemini)

// Plugin descriptor
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
    .name = "DHT20 Sensor (gemini)",
    .description = "Displays Temperature and Humidity from DHT20.",
    .new_instance = dht20_constructor,
    .expand_available = FALSE,
    .expand_default = FALSE
};