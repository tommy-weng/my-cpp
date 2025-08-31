#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <lxpanel/plugin.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DHT20_ADDR 0x38  // DHT20 I2C地址

typedef struct {
    GtkWidget *label;
    int fd;
    guint timeout_id;
} DHT20Plugin;

// 读取DHT20传感器数据
static gboolean read_dht20_data(DHT20Plugin *dht20, float *temperature, float *humidity) {
    if (dht20->fd < 0) {
        return FALSE;
    }

    // 触发测量命令
    unsigned char cmd[3] = {0xAC, 0x33, 0x00};
    if (write(dht20->fd, cmd, 3) != 3) {
        return FALSE;
    }
    
    usleep(80000);  // 等待测量完成
    
    // 读取7字节数据
    unsigned char data[7];
    if (read(dht20->fd, data, 7) != 7) {
        return FALSE;
    }
    
    // 检查状态位
    if (data[0] & 0x80) {
        return FALSE;  // 传感器忙
    }
    
    // 解析湿度 (20位: data[1][7:0] + data[2][7:0] + data[3][7:4])
    unsigned int raw_humidity = ((unsigned int)data[1] << 12) |
                               ((unsigned int)data[2] << 4) |
                               ((unsigned int)data[3] >> 4);
    *humidity = (float)raw_humidity * 100.0 / 1048576.0;
    
    // 解析温度 (20位: data[3][3:0] + data[4][7:0] + data[5][7:0])
    unsigned int raw_temp = (((unsigned int)data[3] & 0x0F) << 16) |
                           ((unsigned int)data[4] << 8) |
                           (unsigned int)data[5];
    *temperature = (float)raw_temp * 200.0 / 1048576.0 - 50.0;
    
    return TRUE;
}

// 更新显示数据的回调函数
static gboolean update_sensor_data(gpointer user_data) {
    DHT20Plugin *dht20 = (DHT20Plugin *)user_data;
    float temperature, humidity;
    char display_text[64];
    
    if (read_dht20_data(dht20, &temperature, &humidity)) {
        snprintf(display_text, sizeof(display_text), "温度: %.1f°C 湿度: %.1f%%", temperature, humidity);
        gtk_label_set_text(GTK_LABEL(dht20->label), display_text);
    } else {
        gtk_label_set_text(GTK_LABEL(dht20->label), "传感器读取失败");
    }
    
    return TRUE;  // 继续定时器
}

// 插件构造函数
static GtkWidget *dht20_new_instance(LXPanel *panel, config_setting_t *settings) {
    DHT20Plugin *dht20 = g_new0(DHT20Plugin, 1);
    
    // 初始化I2C
    dht20->fd = wiringPiI2CSetup(DHT20_ADDR);
    if (dht20->fd < 0) {
        GtkWidget *label = gtk_label_new("I2C初始化失败");
        gtk_widget_show(label);
        return label;
    }
    
    // 等待传感器启动
    usleep(100000);
    
    // 创建显示标签
    dht20->label = gtk_label_new("初始化中...");
    gtk_widget_show(dht20->label);
    
    // 设置定时器，每2秒更新一次数据
    dht20->timeout_id = g_timeout_add_seconds(2, update_sensor_data, dht20);
    
    // 将插件数据存储在widget中
    lxpanel_plugin_set_data(dht20->label, dht20, (GDestroyNotify)g_free);
    
    return dht20->label;
}

// 插件析构函数
static void dht20_destructor(gpointer user_data) {
    DHT20Plugin *dht20 = (DHT20Plugin *)user_data;
    
    if (dht20) {
        // 停止定时器
        if (dht20->timeout_id > 0) {
            g_source_remove(dht20->timeout_id);
        }
        
        // 关闭I2C设备
        if (dht20->fd >= 0) {
            close(dht20->fd);
        }
    }
}

// 定义模块
FM_DEFINE_MODULE(lxpanel_gtk, dht20_plugin)

// 插件配置
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
    .name = "DHT20温湿度传感器",
    .description = "实时显示DHT20温湿度传感器数据",
    .new_instance = dht20_new_instance,
    .one_per_system = 1,
};