cmake_minimum_required(VERSION 3.12)


file(GLOB NodeCodeSrc
../include/*.h
*.cpp)

add_executable(NodeCode ${NodeCodeSrc})