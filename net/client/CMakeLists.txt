cmake_minimum_required(VERSION 3.10)
project(net_client LANGUAGES CXX)

# 仅在 Windows 工具链下构建客户端
if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "跳过客户端构建（需要 Windows 工具链）")
    return()
endif()

add_executable(net_client client_win.cpp)

target_compile_definitions(net_client PRIVATE _WIN32_WINNT=0x0601)
target_compile_options(net_client PRIVATE -municode)
target_link_libraries(net_client PRIVATE ws2_32 iphlpapi)
target_link_options(net_client PRIVATE -mwindows -static)