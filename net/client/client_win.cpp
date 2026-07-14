#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cstdint>
#include <array>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")

constexpr unsigned short DISCOVERY_PORT = 30000;
constexpr unsigned short CONFIG_PORT = 30001;
constexpr char DISCOVERY_REQUEST[] = "MYCPP_DISCOVER";
constexpr char DISCOVERY_RESPONSE_PREFIX[] = "MYCPP_SERVER_HERE:";
constexpr int WM_APP_SCAN_COMPLETE = WM_APP + 1;
HWND hListBox = nullptr;
HWND hStatus = nullptr;
HWND hIpEdit = nullptr;

std::string utf8FromWide(const std::wstring& wide)
{
    if (wide.empty()) return {};
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wide.data(), static_cast<int>(wide.size()), nullptr, 0, nullptr, nullptr);
    std::vector<char> buffer(sizeNeeded);
    int written = WideCharToMultiByte(CP_UTF8, 0, wide.data(), static_cast<int>(wide.size()), buffer.data(), sizeNeeded, nullptr, nullptr);
    if (written <= 0)
    {
        return {};
    }
    return std::string(buffer.data(), written);
}

std::wstring wideFromUtf8(const std::string& utf8)
{
    if (utf8.empty()) return {};
    int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), nullptr, 0);
    std::vector<wchar_t> buffer(sizeNeeded);
    int written = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), static_cast<int>(utf8.size()), buffer.data(), sizeNeeded);
    if (written <= 0)
    {
        return {};
    }
    return std::wstring(buffer.data(), written);
}

std::vector<std::string> getBroadcastTargets()
{
    std::vector<std::string> targets;
    std::set<std::string> seen;

    ULONG bufferSize = 0;
    if (GetIpAddrTable(nullptr, &bufferSize, 0) == ERROR_INSUFFICIENT_BUFFER)
    {
        auto* table = reinterpret_cast<MIB_IPADDRTABLE*>(new char[bufferSize]);
        if (GetIpAddrTable(table, &bufferSize, 0) == NO_ERROR)
        {
            for (DWORD i = 0; i < table->dwNumEntries; ++i)
            {
                const auto& entry = table->table[i];
                if (entry.dwAddr == 0 || entry.dwMask == 0)
                {
                    continue;
                }

                in_addr addr{};
                addr.S_un.S_addr = entry.dwAddr;
                std::string ip = inet_ntoa(addr);
                if (ip.rfind("127.", 0) == 0)
                {
                    continue;
                }

                uint32_t hostIp = ntohl(entry.dwAddr);
                uint32_t hostMask = ntohl(entry.dwMask);
                uint32_t broad = hostIp | (~hostMask);
                in_addr broadAddr{};
                broadAddr.S_un.S_addr = htonl(broad);
                std::string broadcast = inet_ntoa(broadAddr);

                if (seen.insert(broadcast).second)
                {
                    targets.push_back(broadcast);
                }
            }
        }
        delete[] reinterpret_cast<char*>(table);
    }

    if (targets.empty())
    {
        targets.push_back("255.255.255.255");
    }

    return targets;
}

std::vector<std::string> discoverServers()
{
    std::vector<std::string> results;
    std::set<std::string> seen;

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
    {
        return results;
    }

    char enable = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable));

    const auto targets = getBroadcastTargets();
    for (const auto& targetIp : targets)
    {
        sockaddr_in target{};
        target.sin_family = AF_INET;
        target.sin_port = htons(DISCOVERY_PORT);
        target.sin_addr.s_addr = inet_addr(targetIp.c_str());
        sendto(sock, DISCOVERY_REQUEST, static_cast<int>(strlen(DISCOVERY_REQUEST)), 0,
               reinterpret_cast<sockaddr*>(&target), sizeof(target));
    }

    timeval timeout{};
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));

    char buffer[512];
    sockaddr_in from{};
    int fromLen = sizeof(from);
    while (true)
    {
        int bytes = recvfrom(sock, buffer, static_cast<int>(sizeof(buffer) - 1), 0,
                             reinterpret_cast<sockaddr*>(&from), &fromLen);
        if (bytes == SOCKET_ERROR)
        {
            int error = WSAGetLastError();
            if (error == WSAETIMEDOUT || error == WSAEWOULDBLOCK)
            {
                break;
            }
            break;
        }

        buffer[bytes] = '\0';
        std::string response(buffer);
        std::string remoteIp = inet_ntoa(from.sin_addr);

        if (response.rfind(DISCOVERY_RESPONSE_PREFIX, 0) == 0)
        {
            std::string payload = response.substr(strlen(DISCOVERY_RESPONSE_PREFIX));
            std::ostringstream entry;
            entry << remoteIp;
            if (!payload.empty())
            {
                entry << " (server-config=" << payload << ")";
            }
            std::string line = entry.str();
            if (seen.insert(line).second)
            {
                results.push_back(line);
            }
        }
        else
        {
            if (seen.insert(remoteIp).second)
            {
                results.push_back(remoteIp);
            }
        }
    }

    closesocket(sock);
    return results;
}

bool sendConfigIp(const std::string& remoteIp, const std::string& newIp, std::string& response)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        response = "socket-error";
        return false;
    }

    sockaddr_in target{};
    target.sin_family = AF_INET;
    target.sin_port = htons(CONFIG_PORT);
    target.sin_addr.s_addr = inet_addr(remoteIp.c_str());

    if (connect(sock, reinterpret_cast<sockaddr*>(&target), sizeof(target)) == SOCKET_ERROR)
    {
        closesocket(sock);
        response = "connect-failed";
        return false;
    }

    std::string request = std::string("SET_IP:") + newIp;
    send(sock, request.c_str(), static_cast<int>(request.size()), 0);

    char buffer[256];
    int bytes = recv(sock, buffer, static_cast<int>(sizeof(buffer) - 1), 0);
    if (bytes > 0)
    {
        buffer[bytes] = '\0';
        response = buffer;
    }
    else
    {
        response = "no-response";
    }

    closesocket(sock);
    return true;
}

void updateStatus(const std::wstring& text)
{
    SetWindowTextW(hStatus, text.c_str());
}

void onScanClicked(HWND hwnd)
{
    updateStatus(L"Scanning local network...");
    std::vector<std::string> servers = discoverServers();
    SendMessageW(hListBox, LB_RESETCONTENT, 0, 0);
    for (const auto& item : servers)
    {
        SendMessageW(hListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(wideFromUtf8(item).c_str()));
    }

    if (servers.empty())
    {
        updateStatus(L"未找到任何服务端设备。");
    }
    else
    {
        updateStatus(L"已发现设备，选择一个 IP 并可设置配置 IP。");
    }
}

void onConfigureClicked(HWND hwnd)
{
    int index = static_cast<int>(SendMessageW(hListBox, LB_GETCURSEL, 0, 0));
    if (index == LB_ERR)
    {
        updateStatus(L"请先选择一个发现的设备。 ");
        return;
    }

    wchar_t selectedText[256];
    SendMessageW(hListBox, LB_GETTEXT, index, reinterpret_cast<LPARAM>(selectedText));
    std::wstring selectedWide(selectedText);
    std::string selectedUtf8 = utf8FromWide(selectedWide);
    std::string remoteIp = selectedUtf8;
    auto pos = selectedUtf8.find(' ');
    if (pos != std::string::npos)
    {
        remoteIp = selectedUtf8.substr(0, pos);
    }

    wchar_t newIp[128];
    GetWindowTextW(hIpEdit, newIp, static_cast<int>(sizeof(newIp) / sizeof(newIp[0])));
    std::string newIpUtf8 = utf8FromWide(newIp);
    if (newIpUtf8.empty())
    {
        updateStatus(L"请输入要配置的 IP。 ");
        return;
    }

    std::string response;
    if (sendConfigIp(remoteIp, newIpUtf8, response))
    {
        std::wstring message = wideFromUtf8("配置结果: " + response);
        updateStatus(message);
    }
    else
    {
        updateStatus(wideFromUtf8("配置失败: " + response));
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        CreateWindowW(L"BUTTON", L"扫描局域网", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                      20, 20, 140, 30, hwnd, reinterpret_cast<HMENU>(1), nullptr, nullptr);
        hListBox = CreateWindowW(L"LISTBOX", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
                                 20, 60, 360, 140, hwnd, nullptr, nullptr, nullptr);
        CreateWindowW(L"STATIC", L"已发现的服务端 IP：", WS_VISIBLE | WS_CHILD,
                      20, 210, 200, 20, hwnd, nullptr, nullptr, nullptr);
        hIpEdit = CreateWindowW(L"EDIT", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
                                20, 240, 220, 28, hwnd, nullptr, nullptr, nullptr);
        CreateWindowW(L"BUTTON", L"设置 IP", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                      250, 240, 130, 28, hwnd, reinterpret_cast<HMENU>(2), nullptr, nullptr);
        hStatus = CreateWindowW(L"STATIC", L"准备扫描。", WS_VISIBLE | WS_CHILD,
                                20, 280, 360, 20, hwnd, nullptr, nullptr, nullptr);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1:
            onScanClicked(hwnd);
            break;
        case 2:
            onConfigureClicked(hwnd);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return 1;
    }

    const wchar_t CLASS_NAME[] = L"MyCppNetClientWindow";
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"局域网设备发现客户端", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 420, 360, nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr)
    {
        WSACleanup();
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    WSACleanup();
    return 0;
}
