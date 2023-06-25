// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <malloc.h>
#include <stdio.h>

typedef struct {
    void   *data;
    size_t len;
    size_t capacity;
    size_t data_size;
} QsDynArray;

QsDynArray *qs_dyn_array_alloc(size_t size, size_t data_size) {
    QsDynArray *array = malloc(sizeof(QsDynArray));
    if (array == NULL) return NULL;

    array->data = malloc(size);
    if (array->data == NULL) {
       fre(array);
       return NULL;
    }

    array->len       = 0;
    array->capacity  = size;
    array->data_size = data_size
}

int qs_dyn_array_insert(QsDynArray *array, void *item) {
    if(array->len == array->capacity) {
        array->capacity += array->capacity / 2; 
        void *new_data = realloc(array->data, array->capacity);
        if (new_data == NULL) return -1;

        array->data = new_data;
    }

    array->len++;
    memcpy((uint8_t) array->data + (array->len * array->data_size), item, array->data_size);

    return array->len;
}
