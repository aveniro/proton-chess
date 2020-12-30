cmake_minimum_required(VERSION 3.17)
project(pcmath C)
set(CMAKE_C_STANDARD 99)

add_library(pcmath src/pcmath.c)
target_include_directories(pcmath PUBLIC ${INCLUDE_DIRECTORIES})

if(ENABLE_TESTING)
    add_library(pcmath-test test/pcmath.test.c)
    target_include_directories(pcmath-test PUBLIC ${INCLUDE_DIRECTORIES})
endif()