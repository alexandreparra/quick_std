// Copyright (C) 2023-2024 Alexandre Parra (duffhd)
// This file is licensed under the BSD 3-Clause.

#pragma once

#include <assert.h>
#include <stdlib.h>

#ifdef QSNAMES
#define QsSpan Span 
#define qs_span_init    span_init 
#define qs_span_foreach span_foreach
#endif

/// A span, or fat pointer, is a structure with a pointer to a raw array and the total array size.
/// This makes operations safer by providing the array size so that we can index it correctly,
/// preventing array decay.

typedef struct {
    void   *buffer;
    size_t size;
} Span;

Span span_init(void *buffer, size_t size) {
    assert(buffer != NULL);
    assert(size != 0);
    
    Span span = { buffer, size };
    return(span);
}

void span_foreach(Span *span, void (*callback)(void *)) {
    for (size_t i = 0; i < span->size; i += 1) {
        callback(span->buffer[i]);
    }
}

