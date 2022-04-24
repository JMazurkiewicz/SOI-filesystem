cmake_minimum_required(VERSION 3.10)

project("SOI-VirtualFilesystem" LANGUAGES C)

add_executable(
    svfs

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

target_include_directories(svfs PUBLIC include)
target_compile_features(svfs PRIVATE c_std_99)

if(MSVC)
    target_compile_definitions(svfs PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
