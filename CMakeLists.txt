cmake_minimum_required(VERSION 3.23)
project(Maze)

set(CMAKE_CXX_STANDARD 11)

add_executable(Maze main.cpp map.h map.cpp)
# 保证exe文件可以直接移植到没有环境的电脑上直接执行。
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
