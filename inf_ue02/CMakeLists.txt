cmake_minimum_required(VERSION 3.21)
project(inf_ue2 C)

set(CMAKE_C_STANDARD 99)

add_executable(inf_ue2 main.c myStruct.h myList.h)
target_link_libraries(inf_ue2 PRIVATE m)