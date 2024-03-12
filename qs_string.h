// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD 3-Clause.

#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef QSNAMES
#define QsString String
#define qs_string_compare  string_compare
#define qs_string_equals   string_equals
#define qs_string_contains string_contains
#endif

typedef struct {
    char  *buffer;
    size_t size;
} String;

String string_init(char *string, size_t size) {
    String str = { string, size };
    return(str);
}

bool string_equals(String *str1, String *str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (str1->size != str2->size) {
        return(false);
    }

    for (size_t i = 0; i < str1->size; i++) {
        if (str1->buffer[i] != str2->buffer[i]) return(false);
    }

    return(true);
}

/// See if the 'self' string is contained inside the 'other' string.
bool string_contains(String *self, String *other) {
    assert(self != NULL);
    assert(other != NULL);

    if (self->size < other->size) return(false);

    for (size_t i = 0; i < (self->size - other->size); i++) {
        if (self->buffer[i] == other->buffer[0]) {
            size_t counter = 0;

            for (size_t j = 0; j < other->size; j++) {
                if (self->buffer[i + j] == other->buffer[j]) {
                    counter += 1;
                } else {
                    break;
                }
            }

            if (counter == other->size) return(true);
        }
    } 

    return(false);
}

