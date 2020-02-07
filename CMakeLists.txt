cmake_minimum_required(VERSION 3.12)
project(NodeCode)

add_subdirectory(src)

target_include_directories(NodeCode PUBLIC include)