cmake_minimum_required(VERSION 3.12)


file(GLOB_RECURSE NodeCodeSrc
../include/*.h
*.cpp
)

add_executable(NodeCode ${NodeCodeSrc})