// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD 3-Clause.

#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct {
    char  *buffer;
    size_t size;
    size_t capacity; // not meant to be used externally
} QsString;

static inline void check_and_realloc_capacity(QsString *string, size_t slice_size) 
{
     if (string->capacity < (slice_size + string->size)) {
        string->capacity = (string->capacity < slice_size)
            ? string->capacity * 2 + slice_size 
            : string->capacity * 2;

        char *new_string_buffer = (char *) realloc(string->buffer, string->capacity);

        if (new_string_buffer != NULL) {
            string->buffer = new_string_buffer;
        }
    }
}

void qs_string_alloc(QsString *string, char *initial_string, size_t initial_size) 
{
    string->capacity = initial_size;
    string->size     = initial_size;
    string->buffer   = (char *) malloc(sizeof(char *) * initial_size);

    if (initial_string != NULL) {
        strcpy(string->buffer, initial_string);
    }
}

void qs_string_empty_alloc(QsString *string, size_t initial_size) 
{
    string->capacity = initial_size;
    string->size     = initial_size;
    string->buffer   = (char *) malloc(sizeof(char *) * initial_size);
}

void qs_string_concat(QsString *string, char *new_slice, size_t slice_size) 
{
    check_and_realloc_capacity(string, slice_size);

    size_t i = 0;
    for (; i < slice_size; i++) {
        string->buffer[i + string->size] = new_slice[i];
    }

    string->buffer[i + string->size] = '\0';

    string->size += slice_size;
}

