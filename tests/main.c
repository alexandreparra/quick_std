#include <stdbool.h>
#include <stdio.h>

#include "../qs_arena.h"
#include "../qs_array.h"
#include "../qs_string_util.h"
#include "../qs_typed_array.h"
#include "../qs_ring_buffer.h"

#define RED   "\033[0;31m"
#define GREEN "\033[0;32m"
#define WHITE "\033[0m"

#define QS_ASSERT_TRUE(expr, test_message) expr ? printf("%sTEST PASSED %s%s\n", GREEN, WHITE, test_message) \
                                                : printf("%sTEST FAILED %s%s\n", RED, WHITE, test_message)

#define QS_PRINT_WHITE(message) printf("%s%s", WHITE, message)

void test_string_contains(void) {
    QS_PRINT_WHITE("qs_string_contains TESTS\n");

    bool result;

    result = null_string_contains("some long phrase", "long");
    QS_ASSERT_TRUE(result, "comparison 'some long phrase' -> long");

    result = null_string_contains("long", "long");
    QS_ASSERT_TRUE(result, "comparison long -> long");

    result = null_string_contains("long", "g");
    QS_ASSERT_TRUE(result, "comparison long -> long");

    result = null_string_contains("lonlong", "long");
    QS_ASSERT_TRUE(result, "comparison lonlong -> long");
}

void test_string_copy_slice(void) {
    QS_PRINT_WHITE("\nqs_string_copy_slice TESTS\n");
    char *phrase = "some long phrase";
    char dest[5];

    qs_string_copy_slice(phrase, 5, 8, dest);

    QS_ASSERT_TRUE(strcmp(dest, "long") == 0, "copy slice");
}

void test_array(void) {
    QS_PRINT_WHITE("\nqs_dyn_array TESTS\n");
    Array int_array = array_alloc(2, sizeof(int));

    int i1 = 1;

    array_append(&int_array, &i1);
    int *pos_0 = array_get(&int_array, 0);
    QS_ASSERT_TRUE(*pos_0 == 1, "Assert array position 0 to value 1");

    int i2 = 2;
    array_append(&int_array, &i2);
    int *pos_1 = array_get(&int_array, 1);
    QS_ASSERT_TRUE(*pos_1 == 2, "Assert array position 1 to value 2");

    int i3 = 3;
    array_append(&int_array, &i3);
    int *pos_2 = array_get(&int_array, 2);
    QS_ASSERT_TRUE(*pos_2 == 3, "Assert array position 2 to value 3 with realloc");

    array_get(&int_array, 5);
    array_free(&int_array);
}

QS_DYN_ARRAY_DEFINE(int);
void test_typed_dyn_array(void) {
    QS_PRINT_WHITE("\nqs_typed_dyn_array TESTS\n");

    QsDynArray_int *int_array = qs_array_int_alloc(2);

    int i1 = 1;

    qs_array_int_append(int_array, &i1);
    int *pos_0 = qs_array_int_get(int_array, 0);
    QS_ASSERT_TRUE(*pos_0 == 1, "Assert array position 0 to value 1");

    int i2 = 2;
    qs_array_int_append(int_array, &i2);
    int *pos_1 = qs_array_int_get(int_array, 1);
    QS_ASSERT_TRUE(*pos_1 == 2, "Assert array position 1 to value 2");

    int i3 = 3;
    qs_array_int_append(int_array, &i3);
    int *pos_2 = qs_array_int_get(int_array, 2);
    QS_ASSERT_TRUE(*pos_2 == 3, "Assert array position 2 to value 3 with realloc");

    qs_array_int_free(int_array);
}

void test_ring_buffer(void)
{
    QS_PRINT_WHITE("\nqs_ring_buffer TESTS\n");

    int *rb_buffer = malloc(3 * sizeof(int));
    RingBuffer rb = ring_buffer_alloc(rb_buffer, 3, sizeof(int));

    int i1 = 1;
    ring_buffer_write(&rb, &i1);

    int i2 = 2;
    ring_buffer_write(&rb, &i2);

    int i3 = 3;
    ring_buffer_write(&rb, &i3);

    int *i = NULL;
    i = ring_buffer_read(&rb);
    QS_ASSERT_TRUE(*i == 1, "Position 1 of ring buffer is 1");

    i = ring_buffer_read(&rb);
    QS_ASSERT_TRUE(*i == 2, "Position 2 of ring buffer is 2");

    i = ring_buffer_read(&rb);
    QS_ASSERT_TRUE(*i == 3, "Position 3 of ring buffer is 3");

    int i4 = 4;
    ring_buffer_write(&rb, &i4);

    i = ring_buffer_read(&rb);
    QS_ASSERT_TRUE(*i == 4, "Position 1 of ring buffer is 4 (start of buffer again)");

    i = ring_buffer_read(&rb);
    QS_ASSERT_TRUE(*i == 2, "Position 2 of ring buffer is 2");

    free(rb_buffer);
}

void test_arena(void) {
    QS_PRINT_WHITE("\nqs_arena TESTS\n");

    char arena_buffer[8];
    Arena arena = arena_init(&arena_buffer, 8);
    if (sizeof(void *) == 8) {
        // Because the default alignment is sizeof(void *), in 64bit architectures
        // an Arena with only 8 bytes of size can't properly hold 2 ints, that's because
        // the first int takes 4 bytes, and the next int starts at the default architecture
        // alignment, which is 8, meaning that for this to succeed we would need 12 bytes in
        // the arena.
        int *i1 = arena_alloc(&arena, sizeof(int));
        QS_ASSERT_TRUE(i1 != NULL, "First arena allocation of an int is not null");
        int *i2 = arena_alloc(&arena, sizeof(int));
        QS_ASSERT_TRUE(i2 == NULL, "Second int allocation fails because of the default alignment");
    }

    if (sizeof(void *) == 4) {
        int *i1 = arena_alloc(&arena, sizeof(int));
        QS_ASSERT_TRUE(i1 != NULL, "Arena allocation of int on 32bits architecture is correct");
        int *i2 = arena_alloc(&arena, sizeof(int));
        QS_ASSERT_TRUE(i2 != NULL, "Second allocation of int doesn't have sufficient size");
    }
}

int main() {
    test_string_contains();
    test_string_copy_slice();

    test_array();
    test_typed_dyn_array();

    test_ring_buffer();

    test_arena();
    return 0;
}
