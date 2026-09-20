/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (C) 2026 PANDA Coop */

#include "bg_eik.h"

#include <stdio.h>
#include <string.h>

/*
 * A small hardcoded subset of test-vectors/eik.json.
 * The full set is exercised by the binding test suites.
 */

static const char *const VALID[] = {
    "942765371", "465715114", "323895590", "7052156328043", "8286081237237", "4375734470130",
};

static const char *const INVALID[] = {
    "942765372",      "942865371",     "7052156328044",
    "7052156338043",  "7052156328143", "",
    "94276537",       "9427653710",    "705215632804",
    "70521563280430", " 42765371",     "942765371 ",
    "BG942765371",    "9427a5371",     "94276537x",
    "-42765371",      "70521563a8043", "705215632a043",
    "7052156328a43",  "70521563280a3", "705215632804a",
    "069874219941a",
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static int failures = 0;

static void expect(const char *value, size_t length, bool expected)
{
    bool actual = bg_eik_is_valid(value, length);

    if (actual != expected) {
        printf("FAIL: \"%s\" expected %s, got %s\n", value ? value : "(null)",
               expected ? "valid" : "invalid", actual ? "valid" : "invalid");
        failures++;
    }
}

int main(void)
{
    for (size_t i = 0; i < ARRAY_SIZE(VALID); i++) {
        expect(VALID[i], strlen(VALID[i]), true);
    }
    for (size_t i = 0; i < ARRAY_SIZE(INVALID); i++) {
        expect(INVALID[i], strlen(INVALID[i]), false);
    }

    /* NULL pointer must be rejected, not dereferenced */
    expect(NULL, 9, false);

    /* The string does not have to be NUL-terminated: only `length` bytes are read */
    char unterminated[9];
    memcpy(unterminated, VALID[0], sizeof(unterminated));
    if (!bg_eik_is_valid(unterminated, sizeof(unterminated))) {
        printf("FAIL: unterminated buffer\n");
        failures++;
    }

    if (failures > 0) {
        printf("%d test(s) failed\n", failures);
        return 1;
    }

    printf("core: all tests passed\n");
    return 0;
}
