#pragma once

#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "qs_def.h"

#ifdef QSNAMES
#define QsArena Arena
#define qs_arena_init  arena_init
#define qs_arena_alloc arena_alloc
#define qs_arena_drain arena_drain
#define qs_arena_free  arena_free
#endif

internal int is_power_of_two(uintptr_t x) {
	return (x & (x-1)) == 0;
}

internal uintptr_t align_forward(uintptr_t ptr, size_t align) {
	uintptr_t a, modulo;

	assert(is_power_of_two(align));

	a = (uintptr_t) align;
	// Same as (p % a) but faster as 'a' is a power of two
	modulo = ptr & (a-1);

	if (modulo != 0) { 
        // If 'p' address is not aligned, push the address to the
		// next value which is aligned
		ptr += a - modulo;
	}

	return ptr;
}

typedef struct {
	void     *buffer;
	size_t    buffer_size;
	uintptr_t current_offset;
} Arena;

int arena_init(Arena *arena, size_t init_size) {
    arena->buffer = malloc(init_size);
    if (arena->buffer == NULL) return FAILURE;

    arena->buffer_size    = init_size;
    arena->current_offset = 0;

    return SUCCESS;
}

void *arena_alloc(Arena *arena, size_t size) {
    uintptr_t current_ptr = (uintptr_t) arena->buffer + arena->current_offset; 
    uintptr_t offset      = align_forward(current_ptr, DEFAULT_ALIGN);

    offset -= (uintptr_t) arena->buffer;

    if (offset + size > arena->buffer_size) {
        return NULL;
    }

    arena->current_offset = offset + size;
    void *ptr = &arena->buffer[offset];
    memset(ptr, 0, size);
    return ptr;
}

void arena_drain(Arena *arena) {
	arena->current_offset = 0;
}

void arena_free(Arena *arena) {
    free(arena->buffer);
}
