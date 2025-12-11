cmake_minimum_required(VERSION 3.10)
project(TemplateExample)

set(CMAKE_CXX_STANDARD 17)  # 使用 C++17，更兼容
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件列表
set(SOURCES
    main.cpp
    src/a.cpp
)

# 创建可执行文件
add_executable(template_example ${SOURCES})

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 如果需要编译指示
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(template_example PRIVATE -Wall -Wextra)
endif()