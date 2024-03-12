// Copyright (C) 2023-2024 Alexandre Parra (duffhd)
// This file is licensed under the BSD 3-Clause.

#pragma once

#include <assert.h>
#include <string.h>

#include "qs_def.h"

#ifdef QSNAMES
#define QsArray Array
#define qs_array_init   array_init 
#define qs_array_append array_append
#define qs_array_get    array_get
#endif

typedef struct {
    void   *buffer;
    size_t count;
    size_t capacity;
    size_t data_size;
} Array;

Array array_alloc(size_t buffer_size, size_t data_size) {
    assert((double) buffer_size / (double) data_size == 0);
    void *buffer = malloc(data_size * buffer_size);
    assert(buffer != NULL);
    
    Array array = {
        .buffer    = buffer,
        .count     = 0,
        .capacity  = buffer_size,
        .data_size = data_size,
    };

   return(array);
}

void array_free(Array *array) {
    free(array->buffer);
}

size_t array_append(Array *array, void *item) {
    assert(item != NULL);

    if (array->count == array->capacity) {
        array->capacity += array->capacity * 2;
        void *new_buffer = realloc(array->buffer, array->capacity);

        array->buffer = new_buffer;
    }

    size_t index = array->count++;
    memcpy((u8 *) array->buffer + (index * array->data_size), item, array->data_size);

    return(index);
}

void *array_get(Array *array, size_t pos) {
    assert(pos < array->count);

    return((u8 *) array->buffer + (pos * array->data_size));
}
