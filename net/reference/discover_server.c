#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BROADCAST_PORT 8888
#define DISCOVER_MSG "DISCOVER_DEVICE_REQ"
#define REPLY_MSG "I_AM_A_SMART_DEVICE_v1.0"
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in my_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // 1. 创建 UDP 套接字
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket 创建失败");
        exit(EXIT_FAILURE);
    }

    // 2. 绑定本地端口 (允许接收广播)
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY; // 监听所有网卡
    my_addr.sin_port = htons(BROADCAST_PORT);

    if (bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        perror("绑定端口失败");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("[*] 服务端已启动，等待局域网发现请求...\n");

    // 3. 持续监听广播
    while (1) {
        int len = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (len < 0) {
            perror("接收失败");
            continue;
        }

        buffer[len] = '\0';
        
        // 4. 验证是否为指定的发现口令
        if (strcmp(buffer, DISCOVER_MSG) == 0) {
            printf("[!] 收到来自 %s 的发现请求，正在回应...\n", inet_ntoa(client_addr.sin_addr));
            
            // 向客户端定向回传自身信息
            sendto(sock, REPLY_MSG, strlen(REPLY_MSG), 0, (struct sockaddr*)&client_addr, addr_len);
        }
    }

    close(sock);
    return 0;
}