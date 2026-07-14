#ifndef UNICODE
#define UNICODE
#endif

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <process.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

#define IDC_BUTTON_SCAN 101
#define IDC_LISTBOX_DEVICES 102

#define BROADCAST_PORT 8888
#define BROADCAST_IP "255.255.255.255"
#define DISCOVER_MSG "DISCOVER_DEVICE_REQ"
#define BUFFER_SIZE 1024

// 全局变量
HWND hListBox;
HWND hButton;
BOOL isScanning = FALSE;

// 独立的网络扫描线程
unsigned __stdcall ScanNetworkThread(void* pArguments) {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in broadcast_addr, server_addr;
    char buffer[BUFFER_SIZE];
    BOOL broadcast_permission = TRUE;
    int addr_len = sizeof(server_addr);

    // 初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"[错误] Winsock 初始化失败");
        _endthreadex(0);
        return 0;
    }

    // 创建 UDP Socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"[错误] Socket 创建失败");
        WSACleanup();
        _endthreadex(0);
        return 0;
    }

    // 开启广播权限
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast_permission, sizeof(broadcast_permission));

    // 设置 2 秒超时，防止无限死等
    int timeout = 2000; 
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

    // 配置地址
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);
    broadcast_addr.sin_port = htons(BROADCAST_PORT);

    // 发送广播
    sendto(sock, DISCOVER_MSG, (int)strlen(DISCOVER_MSG), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));

    // 接收响应
    while (isScanning) {
        int len = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
        if (len > 0) {
            buffer[len] = '\0';
            
            // 将接收到的数据和IP转为宽字符并在界面显示
            wchar_t wBuf[512];
            swprintf_s(wBuf, 512, L"[+] 发现设备 -> IP: %S | 响应: %S", inet_ntoa(server_addr.sin_addr), buffer);
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)wBuf);
        } else {
            // 超时或出错，结束扫描
            break;
        }
    }

    SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"[*] 扫描完成。");
    EnableWindow(hButton, TRUE); // 恢复按钮点击
    isScanning = FALSE;
    closesocket(sock);
    WSACleanup();
    _endthreadex(0);
    return 0;
}

// 窗口回调函数（处理界面事件）
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp) {
    switch (uMsg) {
        case WM_CREATE:
            // 创建列表框（用于显示发现的设备）
            hListBox = CreateWindowEx(
                WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
                10, 50, 460, 300, hwnd, (HMENU)IDC_LISTBOX_DEVICES, NULL, NULL
            );

            // 创建“开始扫描”按钮
            hButton = CreateWindow(
                L"BUTTON", L"开始扫描局域网",
                WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                10, 10, 150, 30, hwnd, (HMENU)IDC_BUTTON_SCAN, NULL, NULL
            );
            break;

        case WM_COMMAND:
            if (LOWORD(wp) == IDC_BUTTON_SCAN) {
                // 清空之前的列表
                SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
                SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)L"[*] 正在广播搜索设备...");
                
                // 禁用按钮防连续点击
                EnableWindow(hButton, FALSE);
                isScanning = TRUE;

                // 启动后台扫描线程
                _beginthreadex(NULL, 0, ScanNetworkThread, NULL, 0, NULL);
            }
            break;

        case WM_DESTROY:
            isScanning = FALSE;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wp, lp);
}

// WinMain 主入口
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"NetDiscoverWindow";
    
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, L"局域网设备发现工具 (Win32 C)",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 固定窗口大小
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}