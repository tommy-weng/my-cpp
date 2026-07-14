cmake_minimum_required(VERSION 3.10)
project(my_cpp_net LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(ExternalProject)

# 设置外部项目的默认源目录为当前项目根目录
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# ===== 本机架构服务端 =====
add_subdirectory(server)

# 将本机服务端复制到构建根目录（带后缀）
add_custom_target(copy_native_server ALL
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:net_server>
        ${CMAKE_CURRENT_BINARY_DIR}/net_server_native
    DEPENDS net_server
    COMMENT "Copying native server to build directory"
)

# ===== Windows 客户端 (MinGW 交叉编译) =====
ExternalProject_Add(net_client
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/client"
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/client-mingw"
    CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/toolchains/mingw-x86_64.cmake
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --target net_client
    INSTALL_COMMAND ""
    BUILD_ALWAYS OFF
)

# 将 Windows 客户端复制到构建根目录
ExternalProject_Add_Step(net_client copy_client
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/client-mingw/src/net_client-build/net_client.exe
        ${CMAKE_CURRENT_BINARY_DIR}/net_client.exe
    DEPENDEES build
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/net_client.exe
)

# ===== ARM64 服务端交叉编译 =====
ExternalProject_Add(net_server_arm64
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/server"
    PREFIX "${CMAKE_CURRENT_BINARY_DIR}/server-arm64"
    CMAKE_ARGS
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/toolchains/aarch64-linux-gnu.cmake
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    BUILD_COMMAND ${CMAKE_COMMAND} --build . --target net_server
    INSTALL_COMMAND ""
    BUILD_ALWAYS OFF
)

# 将 ARM64 服务端复制到构建根目录
ExternalProject_Add_Step(net_server_arm64 copy_server
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_BINARY_DIR}/server-arm64/src/net_server_arm64-build/net_server
        ${CMAKE_CURRENT_BINARY_DIR}/net_server_arm64
    DEPENDEES build
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/net_server_arm64
)

# 创建一个便捷的 "all" 目标来构建所有版本
add_custom_target(all_platforms
    DEPENDS net_server copy_native_server net_client net_server_arm64
    COMMENT "Building all platform versions"
)

# 设置输出文件为项目产物
set(OUTPUT_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/net_client.exe
    ${CMAKE_CURRENT_BINARY_DIR}/net_server_native
    ${CMAKE_CURRENT_BINARY_DIR}/net_server_arm64
)
