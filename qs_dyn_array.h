// Copyright (C) 2023 Alexandre Parra (duffhd)
// This file is licensed under the BSD-3-Clause.

#pragma once

#include <stdio.h>

typedef struct {
    void   *data;
    size_t len;
    size_t capacity;
    size_t data_size;
} QsDynArray;

