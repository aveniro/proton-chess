cmake_minimum_required(VERSION 3.17)
project(pcstrings C)
set(CMAKE_C_STANDARD 99)

add_library(pcstrings src/pcstrings.c)
target_link_libraries(pcstrings pcmath)
target_include_directories(pcstrings PUBLIC ${INCLUDE_DIRECTORIES})

if(ENABLE_TESTING)
    add_library(pcstrings-test test/pcstrings.test.c)
    target_include_directories(pcstrings-test PUBLIC ${INCLUDE_DIRECTORIES})
endif()