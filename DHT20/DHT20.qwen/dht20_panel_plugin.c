/**
 * dht20_panel_plugin.c
 * 
 * LXPanel plugin for DHT20 temperature and humidity sensor
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <lxpanel/plugin.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define DHT20_ADDR 0x38  // DHT20 I2C地址

// 插件私有数据结构
typedef struct {
    LXPanel *panel;
    GtkWidget *plugin;
    GtkWidget *label;
    guint timer;
    int fd;
} DHT20Plugin;

// 读取DHT20传感器数据
static gboolean read_dht20_data(DHT20Plugin *dht20) {
    // 触发测量命令
    unsigned char cmd[3] = {0xAC, 0x33, 0x00};
    if (write(dht20->fd, cmd, 3) < 0) {
        gtk_label_set_text(GTK_LABEL(dht20->label), "DHT20: Error");
        return FALSE;
    }
    
    usleep(80000);  // 等待测量完成
    
    // 读取7字节数据
    unsigned char data[7];
    if (read(dht20->fd, data, 7) != 7) {
        gtk_label_set_text(GTK_LABEL(dht20->label), "DHT20: Read Error");
        return FALSE;
    }
    
    // 检查状态位
    if (data[0] & 0x80) {
        gtk_label_set_text(GTK_LABEL(dht20->label), "DHT20: Busy");
        return FALSE;
    }
    
    // 解析湿度 (20位: data[1][7:0] + data[2][7:0] + data[3][7:4])
    unsigned int raw_humidity = ((unsigned int)data[1] << 12) | 
                               ((unsigned int)data[2] << 4) | 
                               ((unsigned int)data[3] >> 4);
    float humidity = (float)raw_humidity * 100.0 / 1048576.0;
    
    // 解析温度 (20位: data[3][3:0] + data[4][7:0] + data[5][7:0])
    unsigned int raw_temp = (((unsigned int)data[3] & 0x0F) << 16) | 
                           ((unsigned int)data[4] << 8) | 
                           (unsigned int)data[5];
    float temperature = (float)raw_temp * 200.0 / 1048576.0 - 50.0;
    
    // 更新显示
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%.1f°C %.1f%%", temperature, humidity);
    gtk_label_set_text(GTK_LABEL(dht20->label), buffer);
    
    return TRUE;
}

// 定时器回调函数
static gboolean update_display(gpointer user_data) {
    DHT20Plugin *dht20 = (DHT20Plugin *)user_data;
    read_dht20_data(dht20);
    return G_SOURCE_CONTINUE;  // 继续定时器
}

// 插件析构函数
static void dht20_destructor(gpointer user_data) {
    DHT20Plugin *dht20 = (DHT20Plugin *)user_data;
    
    // 移除定时器
    if (dht20->timer) {
        g_source_remove(dht20->timer);
        dht20->timer = 0;
    }
    
    // 关闭I2C
    if (dht20->fd >= 0) {
        close(dht20->fd);
    }
}

// 创建插件实例
static GtkWidget *dht20_new_instance(LXPanel *panel, config_setting_t *settings) {
    // 分配插件数据结构
    DHT20Plugin *dht20 = g_new0(DHT20Plugin, 1);
    dht20->panel = panel;
    dht20->fd = -1;
    
    // 初始化I2C
    dht20->fd = wiringPiI2CSetup(DHT20_ADDR);
    if (dht20->fd < 0) {
        g_free(dht20);
        return NULL;
    }
    
    // 等待传感器启动
    usleep(100000);
    
    // 创建插件widget
    dht20->plugin = gtk_event_box_new();
    gtk_widget_set_has_window(dht20->plugin, FALSE);
    
    // 创建标签用于显示温湿度
    dht20->label = gtk_label_new("DHT20: Init...");
    gtk_container_add(GTK_CONTAINER(dht20->plugin), dht20->label);
    
    // 设置标签属性
    gtk_label_set_ellipsize(GTK_LABEL(dht20->label), PANGO_ELLIPSIZE_END);
    gtk_label_set_xalign(GTK_LABEL(dht20->label), 0.5);
    gtk_label_set_yalign(GTK_LABEL(dht20->label), 0.5);
    
    // 第一次读取数据
    read_dht20_data(dht20);
    
    // 设置定时器，每2秒更新一次
    dht20->timer = g_timeout_add_seconds(2, update_display, dht20);
    
    // 将插件数据附加到widget，同时设置析构函数
    lxpanel_plugin_set_data(dht20->plugin, dht20, dht20_destructor);
    
    // 显示所有组件
    gtk_widget_show(dht20->label);
    gtk_widget_show(dht20->plugin);
    
    return dht20->plugin;
}

// 插件初始化结构体
FM_DEFINE_MODULE(lxpanel_gtk, dht20_qwen)

LXPanelPluginInit fm_module_init_lxpanel_gtk = {
    .name = "DHT20 Sensor (QWen)",
    .description = "Display temperature and humidity from DHT20 sensor",
    .new_instance = dht20_new_instance,
    .expand_available = FALSE,
    .expand_default = FALSE
};