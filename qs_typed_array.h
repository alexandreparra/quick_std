// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <memory.h>
#include <stdlib.h>

/**
 * A macro defined array that receives the type of the data inside it, the array struct will be name 
 * as follows:
 * QS_DYN_ARRAY_DEFINE(int)
 * The generated array will have the following name:
 * QsDynArray_int
 */
#define QS_DYN_ARRAY_DEFINE(type) \
                                  \
typedef struct {                  \
    type   *buffer;               \
    size_t count;                 \
    size_t capacity;              \
} QsDynArray_##type;              \
                                  \
QsDynArray_##type *qs_array_##type##_alloc(size_t size) {         \
    QsDynArray_##type *array = malloc(sizeof(QsDynArray_##type)); \
    if (array == NULL) {                                          \
        return NULL;                                              \
    }                                                             \
    array->buffer = malloc(size * sizeof(type));                  \
    if (array->buffer == NULL) {                                  \
        free(array);                                              \
        return NULL;                                              \
    }                                                             \
    array->count    = 0;                                          \
    array->capacity = size;                                       \
    return array;                                                 \
} \
\
void qs_array_##type##_free(QsDynArray_##type *array) {     \
    free(array->buffer);                                    \
    free(array);                                            \
} \
\
size_t qs_array_##type##_append(QsDynArray_##type *array, const type *item) { \
    if(array->count == array->capacity) {                                     \
        array->capacity += array->capacity / 2;                               \
        type *new_buffer = realloc(array->buffer, array->capacity);           \
        if (!new_buffer) return -1;                                           \
        array->buffer = new_buffer;                                           \
    }                                                                         \
                                                                              \
    array->buffer[array->count] = *item;                                      \
    array->count++;                                                           \
    return array->count;                                                      \
} \
\
type *qs_array_##type##_get(QsDynArray_##type *array, size_t index) { \
    if (index > array->count) return NULL;                            \
    return &array->buffer[index];                                     \
}
