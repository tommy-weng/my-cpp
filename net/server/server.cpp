#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
using socklen_t = int;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#endif

constexpr unsigned short DISCOVERY_PORT = 30000;
constexpr unsigned short CONFIG_PORT = 30001;
constexpr char DISCOVERY_REQUEST[] = "MYCPP_DISCOVER";
constexpr char DISCOVERY_RESPONSE_PREFIX[] = "MYCPP_SERVER_HERE:";
constexpr char SET_IP_PREFIX[] = "SET_IP:";
constexpr size_t BUFFER_SIZE = 1024;

static std::string configuredIp = "unset";
static std::mutex configMutex;
static std::atomic<bool> running(true);

#ifdef _WIN32
void cleanupSocketLibrary()
{
    WSACleanup();
}

bool initSocketLibrary()
{
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}

void closeSocket(SOCKET sock)
{
    closesocket(sock);
}
#else
bool initSocketLibrary()
{
    return true;
}

void cleanupSocketLibrary()
{
}

void closeSocket(int sock)
{
    close(sock);
}
#endif

bool setReuseAddr(int sock)
{
    int opt = 1;
    return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt)) == 0;
}

std::string currentConfiguredIp()
{
    std::lock_guard<std::mutex> lock(configMutex);
    return configuredIp;
}

void setConfiguredIp(const std::string& ip)
{
    std::lock_guard<std::mutex> lock(configMutex);
    configuredIp = ip;
}

void runDiscoveryServer()
{
#ifdef _WIN32
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
#else
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
#endif
    if (sock < 0)
    {
        std::cerr << "Failed to create UDP socket." << std::endl;
        return;
    }

    if (!setReuseAddr(sock))
    {
        std::cerr << "Failed to set SO_REUSEADDR." << std::endl;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(DISCOVERY_PORT);

    if (bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        std::cerr << "Failed to bind UDP socket to port " << DISCOVERY_PORT << "." << std::endl;
        closeSocket(sock);
        return;
    }

    std::cout << "Discovery server listening on UDP port " << DISCOVERY_PORT << "." << std::endl;

    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (running)
    {
        int recvLen = recvfrom(sock, buffer, static_cast<int>(BUFFER_SIZE) - 1, 0,
                               reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
        if (recvLen <= 0)
        {
            continue;
        }

        buffer[recvLen] = '\0';
        std::string request(buffer);
        if (request != DISCOVERY_REQUEST)
        {
            continue;
        }

        std::string response = std::string(DISCOVERY_RESPONSE_PREFIX) + currentConfiguredIp();
        sendto(sock, response.c_str(), static_cast<int>(response.size()), 0,
               reinterpret_cast<sockaddr*>(&clientAddr), clientAddrLen);

        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, ipStr, sizeof(ipStr));
        std::cout << "Responded to discovery request from " << ipStr << "." << std::endl;
    }

    closeSocket(sock);
}

void runConfigServer()
{
#ifdef _WIN32
    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    int listener = socket(AF_INET, SOCK_STREAM, 0);
#endif
    if (listener < 0)
    {
        std::cerr << "Failed to create TCP listener socket." << std::endl;
        return;
    }

    if (!setReuseAddr(listener))
    {
        std::cerr << "Failed to set SO_REUSEADDR on TCP socket." << std::endl;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(CONFIG_PORT);

    if (bind(listener, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        std::cerr << "Failed to bind TCP listener to port " << CONFIG_PORT << "." << std::endl;
        closeSocket(listener);
        return;
    }

    if (listen(listener, 4) < 0)
    {
        std::cerr << "Failed to listen on TCP port " << CONFIG_PORT << "." << std::endl;
        closeSocket(listener);
        return;
    }

    std::cout << "Config server listening on TCP port " << CONFIG_PORT << "." << std::endl;

    while (running)
    {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);
#ifdef _WIN32
        SOCKET client = accept(listener, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
#else
        int client = accept(listener, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
#endif
        if (client < 0)
        {
            continue;
        }

        char buffer[BUFFER_SIZE];
        int recvLen = recv(client, buffer, static_cast<int>(BUFFER_SIZE) - 1, 0);
        if (recvLen > 0)
        {
            buffer[recvLen] = '\0';
            std::string request(buffer);
            std::string response;
            if (request.rfind(SET_IP_PREFIX, 0) == 0)
            {
                std::string newIp = request.substr(sizeof(SET_IP_PREFIX) - 1);
                setConfiguredIp(newIp);
                response = "OK:" + newIp;
                std::cout << "Configured IP updated to " << newIp << " from client." << std::endl;
            }
            else
            {
                response = "ERROR:UNSUPPORTED_COMMAND";
            }
            send(client, response.c_str(), static_cast<int>(response.size()), 0);
        }

        closeSocket(client);
    }

    closeSocket(listener);
}

int main()
{
    if (!initSocketLibrary())
    {
        std::cerr << "Failed to initialize sockets." << std::endl;
        return 1;
    }

    std::thread discoveryThread(runDiscoveryServer);
    std::thread configThread(runConfigServer);

    std::cout << "Press Ctrl+C or close the console to stop the server." << std::endl;
    discoveryThread.join();
    configThread.join();

    cleanupSocketLibrary();
    return 0;
}
