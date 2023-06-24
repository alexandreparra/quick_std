// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <memory.h>
#include <stdlib.h>

#define QS_DYN_ARRAY_DEFINE(type) \
                                  \
typedef struct {                  \
    type   *data;                 \
    size_t size;                  \
    size_t capacity;              \
} QsDynArray_##type;              \
                                  \
QsDynArray_##type *qs_dyn_array_alloc(size_t size) \
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
    array->size       = 0;                                        \
    array->capacity = size;                                       \
    return array;                                                 \
} \
\
int qs_dyn_array_append(QsDynArray_##type *array, const type *item) \
{ \
    if(array->size == array->capacity) {         \
        array->capacity += array->capacity / 2;  \
        type *new_data = realloc(array->data, )  \
        if (!new_data) return -1;                \
        array->data = new_data;                  \
    }                                            \
                                                 \
    array->data[array->size] = &item;            \
    array->size++;                               \
    return array->size;                          \
} \
\
type *qs_dyn_array_get(QsDynArray_##type *array, size_t index) \
{ \
    if (index > array->size) return NULL; \
    return &array->data[index];           \
}
