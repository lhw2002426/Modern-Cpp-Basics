# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和使用的语言
project(AnimalProject CXX)

# 设置 C++ 标准（C++11、C++14、C++17、C++20 等）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 包含头文件目录（修改为相对路径）
include_directories(${CMAKE_SOURCE_DIR}/include)

# 可执行文件名称
set(EXECUTABLE_NAME a)

# 方案1：使用明确的源文件列表（推荐）
set(SOURCES 
    main.cpp
    src/a.cpp
)

# 方案2：递归查找源文件
# file(GLOB_RECURSE SOURCES "*.cpp" "src/*.cpp")

# 方案3：只查找当前目录（原来的方法）
# file(GLOB SOURCES "*.cpp")
# 注意：这不会包含 src/ 目录下的文件

# 添加可执行文件
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# 设置输出目录（可选）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)