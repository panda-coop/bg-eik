/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (C) 2026 PANDA Coop */

#include "bg_eik.h"

/*
 * WebAssembly glue.
 *
 * JS cannot pass a string to wasm directly, so the wrapper writes the bytes
 * into this static buffer and then calls bg_eik_check() with the length.
 */

#define INPUT_BUFFER_SIZE 16

static char input_buffer[INPUT_BUFFER_SIZE];

__attribute__((export_name("bg_eik_buffer"))) char *bg_eik_buffer(void)
{
    return input_buffer;
}

__attribute__((export_name("bg_eik_buffer_size"))) int bg_eik_buffer_size(void)
{
    return INPUT_BUFFER_SIZE;
}

__attribute__((export_name("bg_eik_check"))) int bg_eik_check(int length)
{
    if (length < 0 || length > INPUT_BUFFER_SIZE) {
        return 0;
    }
    return bg_eik_is_valid(input_buffer, (size_t)length) ? 1 : 0;
}
