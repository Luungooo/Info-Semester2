cmake_minimum_required(VERSION 3.21)
project(inf_ue6 C)

set(CMAKE_C_STANDARD 99)

add_executable(inf_ue6 main.c binarytree.h)
target_link_libraries(inf_ue6 PRIVATE m)