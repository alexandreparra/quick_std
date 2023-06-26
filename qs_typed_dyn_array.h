// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <memory.h>
#include <stdlib.h>

/**
 * A macro defined array that receives the type of the data inside it, the array struct will be name as follows:
 * QS_DYN_ARRAY_DEFINE(int)
 * The generated array will have the following name:
 * QsDynArray_int
 */
#define QS_DYN_ARRAY_DEFINE(type) \
                                  \
typedef struct {                  \
    type   *data;                 \
    size_t len;                   \
    size_t capacity;              \
} QsDynArray_##type;              \
                                  \
QsDynArray_##type *qs_dyn_array_##type##_alloc(size_t size) \
{ \
    QsDynArray_##type *array = malloc(sizeof(QsDynArray_##type)); \
    if (array == NULL) {                                          \
        return NULL;                                              \
    }                                                             \
    array->data = malloc(size * sizeof(type));                    \
    if (array->data == NULL) {                                    \
        free(array);                                              \
        return NULL;                                              \
    }                                                             \
    array->len      = 0;                                          \
    array->capacity = size;                                       \
    return array;                                                 \
} \
\
void qs_dyn_array_##type##_free(QsDynArray_##type *array) \
{ \
    free(array->data); \
    free(array);       \
} \
size_t qs_dyn_array_##type##_append(QsDynArray_##type *array, const type *item) \
{ \
    if(array->len == array->capacity) {                         \
        array->capacity += array->capacity / 2;                 \
        type *new_data = realloc(array->data, array->capacity); \
        if (!new_data) return -1;                               \
        array->data = new_data;                                 \
    }                                                           \
                                                                \
    array->data[array->len] = *item;                            \
    array->len++;                                               \
    return array->len;                                          \
} \
\
type *qs_dyn_array_##type##_get(QsDynArray_##type *array, size_t index) \
{ \
    if (index > array->len) return NULL;  \
    return &array->data[index];           \
}
