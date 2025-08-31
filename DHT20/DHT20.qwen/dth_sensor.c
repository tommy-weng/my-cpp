#include <wiringPiI2C.h>
#include <stdio.h>
#include <unistd.h>

#define DHT20_ADDR 0x38  // DHT20 I2C地址

int main() {
    int fd = wiringPiI2CSetup(DHT20_ADDR);
    if (fd < 0) {
        printf("Failed to setup I2C\n");
        return 1;
    }

    // 等待传感器启动
    usleep(100000);

    while (1) {
        // 触发测量命令
        unsigned char cmd[3] = {0xAC, 0x33, 0x00};
        write(fd, cmd, 3);
        
        usleep(80000);  // 等待测量完成
        
        // 读取7字节数据
        unsigned char data[7];
        if (read(fd, data, 7) != 7) {
            printf("Failed to read data\n");
            continue;
        }
        
        // 检查状态位
        if (data[0] & 0x80) {
            printf("Sensor busy, retrying...\n");
            continue;
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
        
        printf("Temperature: %.1f °C, Humidity: %.1f %%\n", temperature, humidity);
        
        sleep(2);
    }

    return 0;
}
