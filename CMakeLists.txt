cmake_minimum_required(VERSION 3.10)

project("SOI - Virtual filesystem")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(
    SOURCES

    src/vfs/copy.c
    src/vfs/delete.c
    src/vfs/disk.c
    src/vfs/new.c
    src/vfs/print.c
    src/vfs/remove.c
    src/vfs/stats.c

    src/help.c
    src/main.c
)

add_executable(svfs ${SOURCES})
target_include_directories(svfs PUBLIC include)
