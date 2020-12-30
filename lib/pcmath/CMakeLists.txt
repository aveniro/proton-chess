cmake_minimum_required(VERSION 3.17)
project(pcmath C)
set(CMAKE_C_STANDARD 99)

set(PROTON_CHESS_MATH_INCLUDE_DIRECTORIES
        include)

add_library(pcmath src/pcmath.c)
target_include_directories(pcmath PUBLIC ${PROTON_CHESS_MATH_INCLUDE_DIRECTORIES})