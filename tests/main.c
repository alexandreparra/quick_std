#include <stdbool.h>
#include <stdio.h>

#include "../qs_typed_dyn_array.h"
#include "../qs_string.h"
#include "../qs_unit_test.h"

int main() {
    bool result;

    result = qs_string_contains("some long phrase", "long");
    QS_ASSERT_TRUE(result, "comparison 'some long phrase' -> long");

    result = qs_string_contains("long", "long");
    QS_ASSERT_TRUE(result, "comparison long -> long");

    result = qs_string_contains("long", "g");
    QS_ASSERT_TRUE(result, "comparison long -> long");

    result = qs_string_contains("lonlong", "long");
    QS_ASSERT_TRUE(result, "comparison lonlong -> long");

    char **strings = qs_string_split("some spaced text", ' ');

    QS_ASSERT_TRUE(strcmp(strings[0], "some"),   "split string position 0");
    QS_ASSERT_TRUE(strcmp(strings[1], "spaced"), "split string position 1");
    QS_ASSERT_TRUE(strcmp(strings[2], "text"),   "split string position 2");

    return 0;
}
