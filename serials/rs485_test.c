#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// ======================= 配置区域 =======================
#define UART1_DEV     "/dev/ttyS1"
#define UART2_DEV     "/dev/ttyS2"
// ========================================================

// 标准串口配置（双向通信必须设置合理的超时时间，防止死锁）
int setup_uart(int fd, int baud) {
    struct termios options;
    if (tcgetattr(fd, &options) < 0) return -1;
    
    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);
    
    options.c_cflag &= ~PARENB;        // 无校验
    options.c_cflag &= ~CSTOPB;        // 1位停止位
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;            // 8位数据
    options.c_cflag &= ~CRTSCTS;       // 禁用硬件流控
    options.c_cflag |= (CLOCAL | CREAD);
    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    // 设置非固定阻塞：2秒内有数据就返回，没数据就返回0（超时）
    options.c_cc[VMIN] = 0;            
    options.c_cc[VTIME] = 20;          // 20分秒 = 2秒超时
    
    return tcsetattr(fd, TCSANOW, &options);
}

int main() {
    int fd1, fd2;
    char send_buf[128];
    char recv_buf[128];
    int cycle_count = 0;

    // 1. 两个串口都必须以可读写（O_RDWR）模式打开
    fd1 = open(UART1_DEV, O_RDWR | O_NOCTTY);
    fd2 = open(UART2_DEV, O_RDWR | O_NOCTTY);
    
    if (fd1 < 0 || fd2 < 0) {
        perror("❌ 打开串口设备失败");
        if (fd1 >= 0) close(fd1);
        if (fd2 >= 0) close(fd2);
        return -1;
    }

    // 2. 配置波特率 115200
    if (setup_uart(fd1, B115200) < 0 || setup_uart(fd2, B115200) < 0) {
        perror("❌ 配置串口参数失败");
        close(fd1); close(fd2);
        return -1;
    }

    printf("==================================================\n");
    printf("▶️  开始 RS-485 双向交替乒乓测试（流控测试）...\n");
    printf("   节点 A: %s  <-- 双向交替 -->  节点 B: %s\n", UART1_DEV, UART2_DEV);
    printf("   提示: 按 Ctrl + C 退出测试\n");
    printf("==================================================\n\n");

    while (1) {
        cycle_count++;
        printf("【第 %d 轮交替测试】\n", cycle_count);

        // ------------------------------------------------
        // 阶段一：ttyS1 发送 --> ttyS2 接收
        // ------------------------------------------------
        snprintf(send_buf, sizeof(send_buf), "Ping from ttyS1 [#%d]", cycle_count);
        write(fd1, send_buf, strlen(send_buf));
        tcdrain(fd1); // 确保 ttyS1 数据完全喷出
        
        printf("  [A -> B] 📤 %s 发送: %s\n", UART1_DEV, send_buf);

        // ttyS2 开始接收
        memset(recv_buf, 0, sizeof(recv_buf));
        int rx_bytes2 = read(fd2, recv_buf, sizeof(recv_buf) - 1);
        if (rx_bytes2 > 0) {
            printf("  [A -> B] 📥 %s 收到: \033[32m%s\033[0m\n", UART2_DEV, recv_buf);
        } else {
            printf("  [A -> B] 📥 %s \033[31m接收超时，未收到数据！\033[0m\n", UART2_DEV);
        }

        // 短暂休眠，稳定总线状态
        usleep(500000); // 0.5秒

        // ------------------------------------------------
        // 阶段二：ttyS2 发送 --> ttyS1 接收
        // ------------------------------------------------
        snprintf(send_buf, sizeof(send_buf), "Pong from ttyS2 [#%d]", cycle_count);
        write(fd2, send_buf, strlen(send_buf));
        tcdrain(fd2); // 确保 ttyS2 数据完全喷出
        
        printf("  [B -> A] 📤 %s 发送: %s\n", UART2_DEV, send_buf);

        // ttyS1 开始接收
        memset(recv_buf, 0, sizeof(recv_buf));
        int rx_bytes1 = read(fd1, recv_buf, sizeof(recv_buf) - 1);
        if (rx_bytes1 > 0) {
            printf("  [B -> A] 📥 %s 收到: \033[36m%s\033[0m\n", UART1_DEV, recv_buf);
        } else {
            printf("  [B -> A] 📥 %s \033[31m接收超时，未收到数据！\033[0m\n", UART1_DEV);
        }

        printf("--------------------------------------------------\n");
        sleep(1); // 等待1秒后进入下一轮交替
    }

    close(fd1);
    close(fd2);
    return 0;
}
