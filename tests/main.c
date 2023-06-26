#include <stdbool.h>
#include <stdio.h>

#include "../qs_dyn_array.h"
#include "../qs_string.h"
#include "../qs_typed_dyn_array.h"

#define QS_ASSERT_TRUE(expr, test_message) expr ? printf("TEST PASSED %s\n", test_message) : printf("TEST FAILED %s\n", test_message)

void test_string_contains() {
    printf("qs_string_contains TESTS\n");

    bool result;

    result = qs_string_contains("some long phrase", "long");
    QS_ASSERT_TRUE(result, "comparison 'some long phrase' -> long");

    result = qs_string_contains("long", "long");
    QS_ASSERT_TRUE(result, "comparison long -> long");

    result = qs_string_contains("long", "g");
    QS_ASSERT_TRUE(result, "comparison long -> long");

    result = qs_string_contains("lonlong", "long");
    QS_ASSERT_TRUE(result, "comparison lonlong -> long");
}

void test_string_split() {
    printf("\nqs_string_split TESTS\n");
    char **strings = qs_string_split("some spaced text", ' ');

    QS_ASSERT_TRUE(strcmp(strings[0], "some") == 0,   "split string position 0");
    QS_ASSERT_TRUE(strcmp(strings[1], "spaced") == 0, "split string position 1");
    QS_ASSERT_TRUE(strcmp(strings[2], "text") == 0,   "split string position 2");
}

void test_string_copy_substring() {
    printf("\nqs_string_copy_substring TESTS\n");
    char *phrase = "some long phrase";
    char dest[5];

    qs_string_copy_substring(phrase, 5, 8, dest);

    QS_ASSERT_TRUE(strcmp(dest, "long") == 0, "copy substring");
}

void test_dyn_array() {
    printf("\nqs_dyn_array TESTS\n");
    QsDynArray *int_array = qs_dyn_array_alloc(2, sizeof(int));

    int i = 1;

    qs_dyn_array_append(int_array, &i);
    int *pos_0 = qs_dyn_array_get(int_array, 0);
    QS_ASSERT_TRUE(*pos_0 == 1, "Assert array position 0 to value 1");

    i += 1;
    qs_dyn_array_append(int_array, &i);
    int *pos_1 = qs_dyn_array_get(int_array, 1);
    QS_ASSERT_TRUE(*pos_1 == 2, "Assert array position 1 to value 2");

    i += 1;
    qs_dyn_array_append(int_array, &i);
    int *pos_2 = qs_dyn_array_get(int_array, 2);
    QS_ASSERT_TRUE(*pos_2 == 3, "Assert array position 2 to value 3 with realloc");

    qs_dyn_array_free(int_array);
}

QS_DYN_ARRAY_DEFINE(int);
void test_typed_dyn_array() {
    printf("\nqs_typed_dyn_array TESTS\n");

    QsDynArray_int *int_array = qs_dyn_array_int_alloc(2);

    int i = 1;

    qs_dyn_array_int_append(int_array, &i);
    int *pos_0 = qs_dyn_array_int_get(int_array, 0);
    QS_ASSERT_TRUE(*pos_0 == 1, "Assert array position 0 to value 1");

    i += 1;
    qs_dyn_array_int_append(int_array, &i);
    int *pos_1 = qs_dyn_array_int_get(int_array, 1);
    QS_ASSERT_TRUE(*pos_1 == 2, "Assert array position 1 to value 2");

    i += 1;
    qs_dyn_array_int_append(int_array, &i);
    int *pos_2 = qs_dyn_array_int_get(int_array, 2);
    QS_ASSERT_TRUE(*pos_2 == 3, "Assert array position 2 to value 3 with realloc");
}

int main() {
    test_string_contains();
    test_string_split();
    test_string_copy_substring();

    test_dyn_array();
    test_typed_dyn_array();

    return 0;
}
