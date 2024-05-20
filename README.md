## quick_std
Quick std (`qs` for short) is a simple header only library that expands on (the very limited) C
standard library. Some much needed structures that you would need to hand-wire yourself in every
code base can be found here. 

The primary goal is to provide bare bones structures that can be easily used in many programs, 
while being minimal, simple and as flexible as possible. No over generalization, nor high 
specialization will be done for any of the structures here, as they are simple enough, you can 
change them in the best way for your program.

For the time being, the structures are all experimental and are being tested on other code bases.
The API may change drastically, or some headers may be deleted.

### QSNAMES
The data structures and utility functions contained here are mostly named like `Array`, or 
`string_init`, if this collides with some function or other library that you have, simply define in
your build system `QSNAMES` so that the structures and functions take names like: `QsArena`, or
`qs_array_append`.

### qs_arena.h
A simple arena implementation that can return aligned memory from a big allocation, making it 
useful for allocation that share the same lifetime.

### qs_array.h
A dynamic array that can track how much space it has left and increase its size. Its buffer is 
allocated using malloc internally, meaning that a free is required by using `array_free()`.

If you wish to use a custom allocator to provide the buffer to the array, use a Span instead, since 
reallocating the size of a custom allocator, like an Arena, would require much more work, and the
array wouldn't know how to do it internally, making this use case very specialized.

### qs_span.h
A span, or fat pointer, is just a structure that wraps a pointer to a raw array and its size.
Because of array decay in C, we loose the size information for raw arrays when passing them to
functions. Wrapping the values in the structure, we can carry around information to safely index 
the raw array.

### qs_string.h
A simple string struct that has a buffer and a size. This eliminates the use of null terminated
strings for **only some use cases**, making it easy to traverse the string and safely know it's 
size.

### qs_string_util.h
Simple null terminated string (also called raw strings here) utilities (not tied to the dedicated 
container string inside `qs_string`).
