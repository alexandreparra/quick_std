#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct {
    void  *buffer;
    size_t length;
    size_t read_at;
    size_t write_at;
    size_t data_size;
} QsRingBuffer;

QsRingBuffer *qs_ring_buffer_alloc(size_t size, size_t data_size)
{
    QsRingBuffer *ring_buffer = malloc(sizeof(QsRingBuffer));
    ring_buffer->buffer    = malloc(data_size * size);
    ring_buffer->length    = size;
    ring_buffer->read_at   = 0;
    ring_buffer->write_at  = 0;
    ring_buffer->data_size = data_size;

    return ring_buffer;
}

void qs_ring_buffer_write(QsRingBuffer *ring_buffer, void *item)
{
    if (ring_buffer->write_at >= ring_buffer->length) {
        ring_buffer->write_at = 0;
    }

    memcpy((uintptr_t *) ring_buffer->buffer + (ring_buffer->write_at * ring_buffer->data_size), item, ring_buffer->data_size);

    ring_buffer->write_at++;
}

void *qs_ring_buffer_read(QsRingBuffer *ring_buffer)
{
    if (ring_buffer->read_at >= ring_buffer->length) {
        ring_buffer->read_at = 0;
    }

    void *item = (uintptr_t *) ring_buffer->buffer + (ring_buffer->read_at * ring_buffer->data_size);
    ring_buffer->read_at++;

    return item;
}

inline void qs_ring_buffer_change_size(QsRingBuffer *ring_buffer, size_t new_size)
{
    ring_buffer->length = new_size;
}

void qs_ring_buffer_free(QsRingBuffer *ring_buffer)
{
    free(ring_buffer->buffer);
    free(ring_buffer);
}
