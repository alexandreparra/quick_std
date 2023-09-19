## quick_std
Quick std (`qs` for short) is a simple header only library that contains additional functionality
to the C programming language including utilities for strings and data structures.

This is only an experimental project to try different ideas and should not be taken seriously.

### qs_dyn_array
Dynamic array (dyn array for short) implementation using C using `void *`.

### qs_typed_dyn_array
The same as the "generic" QsDynArray but the code for the array is generated with a macro:
```c
// Define a new dynamic array using the macro
QS_DYN_ARRAY_DEFINE(int)

// The macro will generate function and struct names based 
// on the type provided for the macro (in this case 'int').
QsDynArray_int *array = qs_dyn_array_int_alloc(5);
```

### qs_linked_list
Generic linked list implemented with `void *`. QsLinkedList maintains internally the size of the data each node
points to, the linked list (QsLinkedList) and nodes (QsNode) are separated structures.

### qs_string
A dedicated container for handling strings and concatenation.

### qs_string_util
Simple string utilities (not tied to the dedicated container string inside `qs_string`).
