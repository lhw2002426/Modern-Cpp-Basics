cmake_minimum_required(VERSION 3.10)
project(TemplateProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 设置源文件
set(SOURCES
    main.cpp
    src/a.cpp
)

# 添加可执行文件
add_executable(template_app ${SOURCES})

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)