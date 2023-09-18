// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "qs_dyn_array.h"

/**
 * Copy a slice from the source string given a start and end index to dest.
 * dest needs to have at least the size of (start + end + 1), the function automatically
 * appends a null terminator '\0' to the end of dest.
 *
 * @param source The source string that's going to have a section of it copied.
 * @param start  The substring start index inside source.
 * @param end    The substring end index inside source.
 * @param dest   The destination in which the section start-to-end from source will be copied. dest needs to have at least
 * the size of (start + end + 1).
 */
void qs_string_copy_slice(const char *source, size_t start, size_t end, char *dest) 
{
    if (start > end) return;

    size_t i;
    for (i = 0; i < end - start + 1; i++)
        dest[i] = source[i + start];
    dest[i] = '\0';
}

/**
 * Check if a given string is contained inside source.
 * @param source      The string which might contain the 'comparison' string.
 * @param comparison  The string which will be compared and seen if its contained inside 'source'.
 * @return            True or false if the string from comparison is contained inside source or not.
 */
bool qs_string_contains(const char *source, const char *comparison) 
{
    size_t source_size     = strlen(source);
    size_t comparison_size = strlen(comparison);

    if (source_size == 0 || comparison_size == 0)
        return false;

    if (comparison_size > source_size)
        return false;

    for (size_t i = 0; i < (source_size - comparison_size + 1); i += 1) {
        if (source[i] == comparison[0]) {
            size_t counter = 0;

            for (size_t j = 0; j < comparison_size; j += 1) {
                if (source[i + j] != comparison[j]) {
                    break;
                } else {
                    counter += 1;
                }
            }

            if (counter == comparison_size)
                return true;
        }
    }

    return false;
}

/**
 * Split the string source given a character split_at and return a list of strings removing the character:
 *
 * \code
 * char *phrase = "some text";
 * QsDynArray *result = qs_string_split(phrase, ' '); // Split at an empty text
 * // result = ["some", "text"]
 * \endcode
 *
 * @param source   The string that will be split.
 * @param split_at The character that delimits where the string will be split.
 * @return Array of strings.
 */
QsDynArray *qs_string_split(const char *source, char split_at) 
{
    size_t default_size  = 5;
    QsDynArray *strings = qs_dyn_array_alloc(default_size, sizeof (char *));

    size_t last_split_index = 0;

    size_t i;
    for (i = 0; source[i] != '\0'; i += 1) {
        if (source[i] == split_at) {
            char *str = malloc(sizeof(char) * (i - last_split_index - 1));
            qs_string_copy_slice(source, last_split_index, i - 1, str); 
            qs_dyn_array_append(strings, str);

            last_split_index = i + 1;
        }
    }

    if (last_split_index < i) {
        char *str = malloc(sizeof(char) * (i - last_split_index - 1));
        qs_string_copy_slice(source, last_split_index, i - 1, str); 
        qs_dyn_array_append(strings, str);
    }
    
    return strings;
}
