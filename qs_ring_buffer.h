#pragma once

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#ifdef QSNAMES
#define QsRingBuffer RingBuffer
#define qs_ring_buffer_init  ring_buffer_init
#define qs_ring_buffer_write ring_buffer_write
#define qs_ring_buffer_read  ring_buffer_read
#endif

typedef struct {
    void  *buffer;
    size_t size;
    size_t read_at;
    size_t write_at;
    size_t data_size;
} RingBuffer;

RingBuffer ring_buffer_alloc(void *buffer, size_t size, size_t data_size) {
    assert(buffer != NULL);


    RingBuffer rb = {
        .buffer    = buffer,
        .size      = size,
        .read_at   = 0,
        .write_at  = 0,
        .data_size = data_size
    };

    return(rb);
}

void ring_buffer_write(RingBuffer *ring_buffer, void *item) {
    if (ring_buffer->write_at >= ring_buffer->size) {
        ring_buffer->write_at = 0;
    }

    memcpy(
        (uintptr_t *) ring_buffer->buffer + (ring_buffer->write_at * ring_buffer->data_size), 
        item, 
        ring_buffer->data_size
    );

    ring_buffer->write_at++;
}

void *ring_buffer_read(RingBuffer *ring_buffer) {
    if (ring_buffer->read_at >= ring_buffer->size) {
        ring_buffer->read_at = 0;
    }

    void *item = (uintptr_t *) ring_buffer->buffer + (ring_buffer->read_at * ring_buffer->data_size);
    ring_buffer->read_at++;

    return(item);
}

