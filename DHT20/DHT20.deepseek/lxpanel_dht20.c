#include <lxpanel/plugin.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>

#define DHT20_ADDR 0x38  // DHT20 I2C地址

// 读取DHT20传感器数据
static int read_dht20(float *temperature, float *humidity) {
    int fd = wiringPiI2CSetup(DHT20_ADDR);
    if (fd < 0) {
        fprintf(stderr, "Failed to setup I2C\n");
        return -1;
    }

    // 触发测量命令
    unsigned char cmd[3] = {0xAC, 0x33, 0x00};
    if (write(fd, cmd, 3) != 3) {
        fprintf(stderr, "Failed to send command\n");
        return -1;
    }

    usleep(80000);  // 等待测量完成

    // 读取7字节数据
    unsigned char data[7];
    if (read(fd, data, 7) != 7) {
        fprintf(stderr, "Failed to read data\n");
        return -1;
    }

    // 检查状态位
    if (data[0] & 0x80) {
        fprintf(stderr, "Sensor busy\n");
        return -1;
    }

    // 解析湿度
    unsigned int raw_humidity = ((unsigned int)data[1] << 12) | 
                               ((unsigned int)data[2] << 4) | 
                               ((unsigned int)data[3] >> 4);
    *humidity = (float)raw_humidity * 100.0 / 1048576.0;

    // 解析温度
    unsigned int raw_temp = (((unsigned int)data[3] & 0x0F) << 16) | 
                           ((unsigned int)data[4] << 8) | 
                           (unsigned int)data[5];
    *temperature = (float)raw_temp * 200.0 / 1048576.0 - 50.0;

    close(fd);
    return 0;
}

// 更新温湿度显示
static gboolean update_sensor_data(GtkWidget *label) {
    float temperature, humidity;
    if (read_dht20(&temperature, &humidity) == 0) {
        char text[64];
        snprintf(text, sizeof(text), "🌡️ %.1f°C | 💧 %.1f%%", temperature, humidity);
        gtk_label_set_text(GTK_LABEL(label), text);
    } else {
        gtk_label_set_text(GTK_LABEL(label), "🌡️ --°C | 💧 --%");
    }
    return TRUE; // 保持定时器运行
}


// 插件构造函数
static GtkWidget *dht20_constructor(LXPanel *panel, config_setting_t *settings) {
    GtkWidget *label = gtk_label_new("🌡️ --°C | 💧 --%");
    gtk_label_set_xalign(GTK_LABEL(label), 0.5); // 居中显示
    g_timeout_add_seconds(2, (GSourceFunc)update_sensor_data, label); // 每2秒更新
    return label;
}

FM_DEFINE_MODULE(lxpanel_gtk, dht20_plugin)

// 插件描述符
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
    .name = "DHT20 Sensor",
    .description = "Display DHT20 temperature/humidity",
    .new_instance = dht20_constructor
};
