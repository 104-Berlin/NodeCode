cmake_minimum_required(VERSION 3.12)
project(NodeCode)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

target_include_directories(NodeCode PUBLIC include)