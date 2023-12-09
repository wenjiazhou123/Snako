
cmake_minimum_required(VERSION 3.24)
project(Snako)

set(CMAKE_CXX_STANDARD 11)

# 添加头文件目录
include_directories(src/Header)

# 指定可执行文件名字和依赖的源文件
add_executable(Snako src/Source/controller.cpp src/Source/food.cpp src/Source/point.cpp src/Source/map.cpp src/Source/startinterface.cpp src/Source/tools.cpp src/Source/snake.cpp main.cpp src/Source/controller.cpp main2.cpp)
