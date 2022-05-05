cmake_minimum_required(VERSION 3.21)
project(inf_ue1 C)

set(CMAKE_C_STANDARD 99)

add_executable(inf_ue1 main.c)
target_link_libraries(inf_ue1 PRIVATE m)