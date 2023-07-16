#include <stdbool.h>
#include <stdio.h>

#include "../qs_dyn_array.h"
#include "../qs_string.h"
#include "../qs_typed_dyn_array.h"
#include "../qs_linked_list.h"

#define RED   "\033[0;31m"
#define GREEN "\033[0;32m"
#define WHITE "\033[0m"

#define QS_ASSERT_TRUE(expr, test_message) expr ? printf("%sTEST PASSED %s%s\n", GREEN, WHITE, test_message) \
                                                : printf("%sTEST FAILED %s%s\n", RED, WHITE, test_message)

#define QS_PRINT_WHITE(message) printf("%s%s", WHITE, message)

void test_string_contains(void) {
    QS_PRINT_WHITE("qs_string_contains TESTS\n");

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

void test_string_split(void) {
    QS_PRINT_WHITE("\nqs_string_split TESTS\n");
    char **strings = qs_string_split("some spaced text", ' ');

    QS_ASSERT_TRUE(strcmp(strings[0], "some") == 0,   "split string position 0");
    QS_ASSERT_TRUE(strcmp(strings[1], "spaced") == 0, "split string position 1");
    QS_ASSERT_TRUE(strcmp(strings[2], "text") == 0,   "split string position 2");
}

void test_string_copy_slice(void) {
    QS_PRINT_WHITE("\nqs_string_copy_slice TESTS\n");
    char *phrase = "some long phrase";
    char dest[5];

    qs_string_copy_slice(phrase, 5, 8, dest);

    QS_ASSERT_TRUE(strcmp(dest, "long") == 0, "copy slice");
}

void test_dyn_array(void) {
    QS_PRINT_WHITE("\nqs_dyn_array TESTS\n");
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
void test_typed_dyn_array(void) {
    QS_PRINT_WHITE("\nqs_typed_dyn_array TESTS\n");

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

    qs_dyn_array_int_free(int_array);
}

void test_linked_list(void) {
    QS_PRINT_WHITE("\nqs_linked_list TESTS\n");
    int ret = 1;
    int i   = 1;

    QsLinkedList *list = qs_linked_list_alloc(&i, sizeof(int));
    int *pos_0 = qs_linked_list_get(list, 0);
    QS_ASSERT_TRUE(*pos_0 == 1, "Assert list position 0 to value 1");

    i += 1;
    qs_linked_list_append(list, &i);
    int *pos_1 = qs_linked_list_get(list, 1);
    QS_ASSERT_TRUE(*pos_1 == 2, "Assert list position 1 to value 2");

    i += 1;
    qs_linked_list_append(list, &i);
    int *pos_2 = qs_linked_list_get(list, 2);
    QS_ASSERT_TRUE(*pos_2 == 3, "Assert list position 2 to value 3");

    ret = qs_linked_list_remove(list, 2);
    QS_ASSERT_TRUE(ret == 0, "Remove value 3 from position 2");

    ret = qs_linked_list_remove(list, 1);
    QS_ASSERT_TRUE(ret == 0, "Remove value 2 from position 1");

    ret = qs_linked_list_remove(list, 0);
    QS_ASSERT_TRUE(ret == 0, "Remove value 1 from position 0");
}

int main() {
    test_string_contains();
    test_string_split();
    test_string_copy_slice();

    test_dyn_array();
    test_typed_dyn_array();

    test_linked_list();

    return 0;
}
