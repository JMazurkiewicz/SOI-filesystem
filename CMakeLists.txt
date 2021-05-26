cmake_minimum_required(VERSION 3.10)

project("SOI - Virtual filesystem")

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)

set(
    SOURCES

    src/help.c
    src/main.c
    
    src/vfs/new_vfs.c
    src/vfs/super_block.c
)

add_executable(svfs ${SOURCES})
target_include_directories(svfs PUBLIC include)
