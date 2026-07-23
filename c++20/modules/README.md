# C++20 Modules GCC & CMake 实战与避坑指南

本指南整合记录了在 **Linux (Ubuntu)** 环境下，使用 **GCC** 与 **CMake** 编译和构建 C++20 Modules 的全套流程、现代标准配置（CMake >= 3.28）、旧版兼容配置（GCC 11 / CMake < 3.28）以及常见踩坑解决方案。

---

## 1. 项目源代码结构

```text
c++20/modules/
├── CMakeLists.txt     # CMake 构建脚本
├── mathutils.cppm     # 模块接口文件
└── main.cpp           # 主程序文件
```

### 1.1 模块接口文件：`mathutils.cppm`
```cpp
export module mathutils; // 声明模块名称为 mathutils

// 导出 add 函数
export int add(int a, int b) {
    return a + b;
}
```

### 1.2 主程序文件：`main.cpp`
```cpp
#include <iostream>     // 在 GCC 11/12 下推荐对系统标准库使用传统 #include
import mathutils;          // 导入自定义模块

int main() {
    std::cout << "3 + 5 = " << add(3, 5) << std::endl;
    return 0;
}
```

---

## 2. 构建方式 A：命令行手动编译（分步顺序）

由于 GCC 命令行在单次调用时**不会自动解析模块依赖顺序**，并且**默认不认识 `.cppm` 扩展名**，必须严格按照以下顺序执行：

```bash
# 步骤 1：彻底清理历史缓存
rm -rf gcm.cache *.o main

# 步骤 2：编译模块接口，生成 gcm.cache 缓存与 mathutils.o 目标文件
# 注意：必须加上 -x c++ 强制指定将 .cppm 当作 C++ 源码编译
g++ -std=c++20 -fmodules-ts -x c++ -c mathutils.cppm -o mathutils.o

# 步骤 3：编译主程序并链接模块
g++ -std=c++20 -fmodules-ts main.cpp mathutils.o -o main

# 步骤 4：运行程序
./main
```

---

## 3. 构建方式 B：使用 CMake 自动化构建

### 3.1 方案 1：现代官方推荐方式（CMake >= 3.28 + Ninja）

**CMake 3.28** 开始原生支持 C++20 Modules 的标准语法 `FILE_SET CXX_MODULES`，能自动进行模块扫描并自动生成依赖编译顺序。推荐配合 **Ninja** 构建工具使用：

#### `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.28)
project(cpp20_modules_demo CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 声明主程序源文件
add_executable(main main.cpp)

# 2. 使用 FILE_SET CXX_MODULES 语法声明 C++20 模块文件
target_sources(main
    PUBLIC
        FILE_SET CXX_MODULES FILES
            mathutils.cppm
)
```

#### 构建与运行
```bash
mkdir -p build && cd build
# CMake >= 3.28 强烈建议搭配 Ninja 生成器以支持自动模块依赖扫描
cmake -G Ninja ..
ninja
./main
```

---

### 3.2 方案 2：向下兼容方案（适用于 GCC 11 / CMake < 3.28 / Make）

如果在旧系统或老版本 CMake (< 3.28) 环境下，`FILE_SET CXX_MODULES` 会触发语法错误。此时需改用传统的配置方式：

#### `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.16)
project(cpp20_modules_demo CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. 直接声明可执行文件及所有源文件
add_executable(main
    mathutils.cppm
    main.cpp
)

# 2. 为目标开启 GCC 模块编译选项
target_compile_options(main PRIVATE -fmodules-ts)

# 3. 关键点：强制指示 GCC 将 .cppm 扩展名识别为 C++ 源码
set_source_files_properties(mathutils.cppm PROPERTIES COMPILE_FLAGS "-x c++")
```

#### 构建与运行
```bash
mkdir -p build && cd build
cmake ..
make
./main
```

---

## 4. 常见报错全汇总与故障排查 (Troubleshooting)

### ❓ 报错 1：`g++: warning: linker input file unused` 或 `Cannot find source file: FILE_SET`
* **原因**：
  * 手动编译时，GCC 默认将 `.cppm` / `.ixx` 识别为链接器输入而不是源码，导致跳过编译。
  * CMake 报错 `Cannot find source file: FILE_SET` 是因为当前 CMake 版本低于 3.28，无法识别现代模块语法。
* **解决**：
  * 命令行编译添加 `-x c++` 参数。
  * 若 CMake < 3.28，请使用**方案 2（传统兼容配置）**；若要使用 `FILE_SET`，请升级 CMake >= 3.28 并在 `cmake_minimum_required` 中明确声明 `VERSION 3.28`。

### ❓ 报错 2：`mathutils: error: failed to read compiled module: No such file or directory`
* **原因**：编译 `main.cpp` 时在当前/缓存目录下找不到 `gcm.cache/mathutils.gcm`。
* **解决**：确保先单独编译了 `mathutils.cppm` 并成功生成了 `gcm.cache/`；检查 `mathutils.cppm` 顶部是否包含了 `export module mathutils;` 声明。

### ❓ 报错 3：`/usr/include/c++/11/iostream: error: failed to read compiled module`
* **原因**：在 `main.cpp` 中写了 `import <iostream>;`[cite: 3]。在 GCC 机制下，使用 `import` 导入系统头文件要求该头文件必须先被预编译为模块接口[cite: 3]。
* **解决**：
  1. **推荐**：在 `main.cpp` 中将系统标准库改回传统的 `#include <iostream>`[cite: 3]。
  2. **预编译**：手动运行 `g++ -std=c++20 -fmodules-ts -x c++-header /usr/include/c++/11/iostream` 生成标准库缓存。
