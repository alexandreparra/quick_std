// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD 3-Clause.

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    void   *data;
    size_t len;
    size_t capacity;
    size_t data_size;
} QsDynArray;

/**
 * Dynamic array that automatically grows if needed.
 * For the current implementation, memory is not aligned by default, this may slow the array
 * operations. 
 */
QsDynArray *qs_dyn_array_alloc(size_t init_size, size_t data_size) {
    QsDynArray *array = malloc(sizeof(QsDynArray));
    if (array == NULL) return NULL;

    array->data = malloc(init_size * data_size);
    if (array->data == NULL) {
        free(array);
        return NULL;
    }

    array->len       = 0;
    array->capacity  = init_size;
    array->data_size = data_size;

    return array;
}

void qs_dyn_array_free(QsDynArray *array) {
    free(array->data);
    free(array);
}

size_t qs_dyn_array_append(QsDynArray *array, void *item) {
    if (array->len == array->capacity) {
        array->capacity += array->capacity / 2;
        void *new_data = realloc(array->data, array->capacity);
        if (new_data == NULL) return -1;

        array->data = new_data;
    }

    size_t index = array->len++;
    memcpy((uint8_t *) array->data + (index * array->data_size), item, array->data_size);

    return index;
}

void *qs_dyn_array_get(QsDynArray *array, size_t pos) {
    if (pos > array->len) return NULL;

    return (uint8_t *) array->data + (pos * array->data_size);
}
