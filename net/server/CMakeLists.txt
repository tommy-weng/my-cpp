cmake_minimum_required(VERSION 3.10)
project(net_server LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(net_server server.cpp)

# 根据平台选择链接库
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(net_server PRIVATE ws2_32)
else()
    target_link_libraries(net_server PRIVATE Threads::Threads)
endif()