# 局域网设备发现程序

本目录包含一个跨平台的网络设备发现和配置系统，采用模块化设计，支持一次构建生成多平台目标。

## 目录结构

```
net/
├── client/
│   ├── client_win.cpp          # Windows GUI 客户端源码
│   └── CMakeLists.txt          # 客户端构建配置
├── server/
│   ├── server.cpp              # 服务端源码
│   └── CMakeLists.txt          # 服务端构建配置
├── toolchains/
│   ├── mingw-x86_64.cmake      # Windows 交叉编译工具链 (x86_64)
│   └── aarch64-linux-gnu.cmake # ARM64 交叉编译工具链
├── CMakeLists.txt              # 顶层构建配置（支持多平台一次构建）
└── README.md
```

## 功能说明

### 客户端 (client_win.cpp)

Windows GUI 客户端，功能包括：
- 扫描局域网发现服务端设备
- 显示发现的设备 IP 地址
- 向服务端发送配置 IP 请求

### 服务端 (server.cpp)

跨平台服务端程序，功能包括：
- 监听 UDP 端口 `30000`，响应局域网发现请求
- 监听 TCP 端口 `30001`，接收配置请求
- 支持多平台：Linux、Windows、ARM64

## 构建说明

### 🚀 一次构建所有平台（推荐）

使用本机 CMake 配置，同时生成 Windows 客户端、本机服务端和 ARM64 服务端：

```bash
cd net
mkdir build && cd build
cmake ..
cmake --build .
```

生成的可执行文件：
- `net_client.exe` - Windows 客户端（MinGW 交叉编译）
- `net_server_native` - 本机架构服务端
- `net_server_arm64` - ARM64 架构服务端

或者使用便捷目标：

```bash
cmake --build . --target all_platforms
```

### 📦 单独构建特定平台

#### 编译 Windows 客户端 (x86_64)

```bash
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/mingw-x86_64.cmake
cmake --build . --target net_client
```

#### 编译 ARM64 服务端

```bash
mkdir build-arm64 && cd build-arm64
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchains/aarch64-linux-gnu.cmake
cmake --build . --target net_server
```

#### 编译本机架构服务端

```bash
mkdir build-native && cd build-native
cmake ..
cmake --build . --target net_server
```

## 依赖安装

### Windows 交叉编译 (MinGW-w64)

```bash
sudo apt update
sudo apt install mingw-w64
```

### ARM64 交叉编译

```bash
sudo apt update
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu libc6-dev-arm64-cross
```

## 使用说明

### 服务端

1. 在目标平台上运行对应的服务端程序：
   - 本机：`./net_server_native`
   - ARM64：`./net_server_arm64`
2. 程序会监听 UDP `30000` 和 TCP `30001` 端口
3. 按下 Ctrl+C 停止服务端

### 客户端 (Windows)

1. 将 `net_client.exe` 复制到 Windows 机器
2. 运行 `net_client.exe`
3. 点击"扫描局域网"按钮
4. 若找到服务端设备，会显示其 IP 地址
5. 选择一个设备，在编辑框中输入要配置的 IP
6. 点击"设置 IP"按钮发送配置请求

## 协议说明

### 发现协议 (UDP 30000)

**客户端请求**：
```
MYCPP_DISCOVER
```

**服务端响应**：
```
MYCPP_SERVER_HERE:<configured_ip>
```

### 配置协议 (TCP 30001)

**客户端请求**：
```
SET_IP:<new_ip>
```

**服务端响应**：
```
OK:<new_ip>
```
或
```
ERROR:UNSUPPORTED_COMMAND
```

## 平台兼容性

| 平台 | 架构 | 编译器 | 状态 |
|------|------|--------|------|
| Linux | x86_64 | gcc/g++ | ✅ 支持 |
| Linux | ARM64 | aarch64-linux-gnu-gcc/g++ | ✅ 支持 |
| Windows | x86_64 | MinGW-w64 | ✅ 支持 (客户端) |
| Windows | x86_64 | MSVC | ✅ 支持 (服务端) |

## 技术特点

1. **模块化设计**：client 和 server 完全独立，可单独构建
2. **一次构建多平台**：使用 CMake ExternalProject 同时构建多个架构
3. **灵活交叉编译**：每个项目可独立指定工具链
4. **标准 CMake 实践**：使用 `add_subdirectory` 和 `ExternalProject` 组织项目结构
5. **跨平台支持**：服务端支持 Linux 和 Windows 多种架构
6. **静态链接**：Windows 客户端静态链接，无需额外依赖

## 故障排除

### MinGW 编译问题

如果遇到找不到 `ws2_32` 或 `iphlpapi` 库的问题，确保已正确安装 MinGW-w64：

```bash
dpkg -L mingw-w64 | grep libws2_32
```

### ARM64 交叉编译问题

如果找不到 `aarch64-linux-gnu-gcc`，需要安装交叉编译工具链：

```bash
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu libc6-dev-arm64-cross
```

### 一次构建失败

如果在一次构建过程中某个平台失败，可以单独构建该平台：

```bash
cmake --build . --target net_client          # 仅 Windows 客户端
cmake --build . --target net_server          # 仅本机服务端
cmake --build . --target net_server_arm64    # 仅 ARM64 服务端
