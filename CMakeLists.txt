cmake_minimum_required(VERSION 3.25)
project(quick_std C)

set(CMAKE_C_STANDARD 17)

add_library(quick_std INTERFACE
        qs_dyn_array.h
        qs_typed_dyn_array.h
        qs_string.h)
