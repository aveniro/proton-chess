cmake_minimum_required(VERSION 3.17)
project(pcmem C)
set(CMAKE_C_STANDARD 99)

set(PROTON_CHESS_MEM_INCLUDE_DIRECTORIES
        include)

add_library(pcmem src/pcmem.c)
target_include_directories(pcmath PUBLIC ${PROTON_CHESS_MATH_INCLUDE_DIRECTORIES})