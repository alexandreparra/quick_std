cmake_minimum_required(VERSION 3.25)
project(quick_std_tests C)

set(CMAKE_C_STANDARD 17)
add_compile_definitions(QSNAMES)

add_executable(quick_std main.c
        ../qs_arena.h
        ../qs_typed_array.h
        ../qs_string.h
        ../qs_string_util.h
        ../qs_array.h

        ../qs_def.h
)
