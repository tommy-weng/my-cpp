#include <stdlib.h>
#include <glib/gi18n.h>
#include <lxpanel/plugin.h>
#include <wiringPiI2C.h>
#include <unistd.h>

#define DHT20_ADDR 0x38  // DHT20 I2C地址

typedef struct {
    GtkWidget *label;
    LXPanel *panel;
    int fd;
    guint timer;
} DHT20Plugin;

static gboolean update_display2(DHT20Plugin *dht) {
    // 触发测量命令
    unsigned char cmd[3] = {0xAC, 0x33, 0x00};
    write(dht->fd, cmd, 3);
    
    usleep(80000);  // 等待测量完成
    
    // 读取7字节数据
    unsigned char data[7];
    if (read(dht->fd, data, 7) != 7) {
        gtk_label_set_text(GTK_LABEL(dht->label), "Failed to read data");
        return TRUE;
    }
    
    // 检查状态位
    if (data[0] & 0x80) {
        gtk_label_set_text(GTK_LABEL(dht->label), "Sensor busy");
        return TRUE;
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
    
    gchar *text = g_strdup_printf("%.1f°C %.1f%%", temperature, humidity);
    gtk_label_set_text(GTK_LABEL(dht->label), text);
    g_free(text);
    
    return TRUE;  // 继续定时器
}

int fd = -1;
static gboolean update_display(GtkWidget *label) {
    // 触发测量命令
    unsigned char cmd[3] = {0xAC, 0x33, 0x00};
    write(fd, cmd, 3);
    
    usleep(80000);  // 等待测量完成
    
    // 读取7字节数据
    unsigned char data[7];
    if (read(fd, data, 7) != 7) {
        gtk_label_set_text(GTK_LABEL(label), "Failed to read data");
        return TRUE;
    }
    
    // 检查状态位
    if (data[0] & 0x80) {
        gtk_label_set_text(GTK_LABEL(label), "Sensor busy");
        return TRUE;
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
    
    gchar *text = g_strdup_printf("%.1f°C %.1f%%", temperature, humidity);
    gtk_label_set_text(GTK_LABEL(label), text);
    g_free(text);
    
    return TRUE;  // 继续定时器
}

static void dht20_destructor(gpointer user_data) {
    DHT20Plugin *dht = (DHT20Plugin *)user_data;
    
    if (dht->timer) {
        g_source_remove(dht->timer);
    }
    
    if (dht->fd >= 0) {
        // 注意：wiringPiI2C没有提供关闭函数，文件描述符会在程序退出时自动关闭
    }
}

static GtkWidget *dht20_constructor2(LXPanel *panel, config_setting_t *settings) {
    DHT20Plugin *dht = g_new0(DHT20Plugin, 1);
    dht->panel = panel;
    
    // 初始化I2C
    dht->fd = wiringPiI2CSetup(DHT20_ADDR);
    if (dht->fd < 0) {
        g_free(dht);
        return NULL;
    }
    
    // 等待传感器启动
    usleep(100000);
    
    // // 创建插件widget
    GtkWidget *plugin = gtk_event_box_new();
    gtk_widget_set_has_window(plugin, FALSE);
    dht->label = gtk_label_new("DHT20: --");
    gtk_widget_show(dht->label);
    gtk_container_add(GTK_CONTAINER(plugin), dht->label);
    
    // 设置数据并启动定时器
    lxpanel_plugin_set_data(plugin, dht, dht20_destructor);
    dht->timer = g_timeout_add_seconds(2, (GSourceFunc) update_display2, dht);
    
    // 首次更新显示
    update_display2(dht);
    
    return plugin;
    // return dht->label;
}

static GtkWidget *dht20_constructor(LXPanel *panel, config_setting_t *settings) {
    GtkWidget *label = gtk_label_new("🌡️ --°C | 💧 --%");
    gtk_label_set_xalign(GTK_LABEL(label), 0.5); // 居中显示
    fd = wiringPiI2CSetup(DHT20_ADDR);
    g_timeout_add_seconds(2, (GSourceFunc)update_display, label); // 每2秒更新
    return label;
}

FM_DEFINE_MODULE(lxpanel_gtk, dht20_plugin)

LXPanelPluginInit fm_module_init_lxpanel_gtk = {
    .name = "DHT20 Sensor (lingma)",
    .description = "Display temperature and humidity from DHT20 sensor",
    .new_instance = dht20_constructor2
};