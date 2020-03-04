cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
project(NodeCode)
add_subdirectory(src)

target_include_directories(NodeCode PUBLIC include)