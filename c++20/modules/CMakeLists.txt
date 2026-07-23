cmake_minimum_required(VERSION 3.16)
project(cpp20_modules_demo CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 声明可执行文件（直接放源文件）
add_executable(main
    mathutils.cppm
    main.cpp
)

# 2. 为编译目标开启 GCC 模块支持
target_compile_options(main PRIVATE -fmodules-ts)

# 3. 告诉 GCC 把 .cppm 强制当作 C++ 源码编译
set_source_files_properties(mathutils.cppm PROPERTIES COMPILE_FLAGS "-x c++")
