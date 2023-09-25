cmake_minimum_required(VERSION 3.25)
project(quick_std C)

set(CMAKE_C_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(quick_std INTERFACE
        qs_dyn_array.h
        qs_linked_list.h
        qs_ring_buffer.h
        qs_string.h
        qs_string_util.h
        qs_typed_dyn_array.h)
