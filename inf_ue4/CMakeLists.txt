cmake_minimum_required(VERSION 3.21)
project(inf_ue4 C)

set(CMAKE_C_STANDARD 99)

add_executable(inf_ue4 main.c myList.h)
target_link_libraries(inf_ue4 PRIVATE m)