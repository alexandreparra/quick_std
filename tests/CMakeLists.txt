cmake_minimum_required(VERSION 3.25)
project(quick_std_tests C)

set(CMAKE_C_STANDARD 17)

add_executable(quick_std main.c ../qs_typed_dyn_array.h ../qs_string.h ../qs_dyn_array.h)
