// Copyright (C) 2023-2024 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "qs_array.h"

#ifdef QSNAMES
#define qs_raw_string_copy_slice raw_string_copy_slice
#define qs_raw_string_compare    raw_string_compare
#endif

/**
 * Copy a slice from the null terminated string 'source' given a start and end index to 'target'.
 * Target needs to have at least the size of (start + end + 1), the function automatically
 * appends a null terminator '\0' to the end of target.
 *
 * @param source The source string that's going to have a section of it copied.
 * @param start  The substring start index inside source.
 * @param end    The substring end index inside source.
 * @param target The target in which the section start-to-end from source will be copied. dest needs 
 *               to have at least
 * the size of (start + end + 1).
 */
void raw_string_copy_slice(const char *source, size_t start, size_t end, char *target)
{
    assert(strlen(source) >= (start + end));
    assert(start < end);

    if (start > end) return;

    size_t i;
    for (i = 0; i < end - start + 1; i++)
        target[i] = source[i + start];
    target[i] = '\0';
}

/**
 * Check if a given null terminated string 'self' is contained inside 'other'.
 * @param source      The string which might contain the 'comparison' string.
 * @param comparison  The string which will be compared and seen if its contained inside 'source'.
 * @return            True or false if the string from comparison is contained inside source or not.
 */
bool raw_string_contains(const char *self, const char *other)
{
    size_t source_size     = strlen(self);
    size_t comparison_size = strlen(other);

    if (source_size == 0 || comparison_size == 0)
        return(false);

    if (comparison_size > source_size)
        return false;

    for (size_t i = 0; i < (source_size - comparison_size + 1); i += 1) {
        if (self[i] == other[0]) {
            size_t counter = 0;

            for (size_t j = 0; j < comparison_size; j += 1) {
                if (self[i + j] != other[j]) {
                    break;
                } else {
                    counter += 1;
                }
            }

            if (counter == comparison_size)
                return(true);
        }
    }

    return(false);
}

