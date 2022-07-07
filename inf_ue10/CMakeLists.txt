cmake_minimum_required(VERSION 3.22)
project(inf_ue10 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS False)
set(SRC_FILES main.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -fcolor-diagnostics -Wall -Winvalid-pch -Wextra -Wpedantic)
