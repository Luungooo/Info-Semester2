cmake_minimum_required(VERSION 3.21)
project(inf_ue5 C)

set(CMAKE_C_STANDARD 99)

add_executable(inf_ue5 main.c)
target_link_libraries(inf_ue5 PRIVATE m)