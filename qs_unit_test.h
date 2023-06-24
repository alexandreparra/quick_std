// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <stdbool.h>

typedef struct {
    char  *test_scope_name;
    size_t number_of_tests;
    size_t failed_tests;
} QsTestContext;

#define QS_ASSERT_TRUE(expr, test_message) expr ? printf("TEST PASSED %s\n", test_message) : printf("TEST FAILED %s\n", test_message)
#define QS_ASSERT_EQUAL(expr) expr ? printf("TEST PASSED\n") : printf("TEST FAILED\n")
