/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (C) 2026 PANDA Coop */

#include "bg_eik.h"

#define EIK9_LENGTH  9
#define EIK13_LENGTH 13

#define EIK9_WEIGHTS_COUNT  8
#define EIK13_WEIGHTS_COUNT 4

/* Index of the first digit covered by the second check of a 13-digit EIK */
#define EIK13_PART_OFFSET 8

static const int EIK9_WEIGHTS_FIRST[EIK9_WEIGHTS_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8};
static const int EIK9_WEIGHTS_SECOND[EIK9_WEIGHTS_COUNT] = {3, 4, 5, 6, 7, 8, 9, 10};

static const int EIK13_WEIGHTS_FIRST[EIK13_WEIGHTS_COUNT] = {2, 7, 3, 5};
static const int EIK13_WEIGHTS_SECOND[EIK13_WEIGHTS_COUNT] = {4, 9, 5, 7};

/* Converts a string into an array of digits. Fails on any non-digit character. */
static bool extract_digits(const char *value, size_t length, int *digits)
{
    for (size_t i = 0; i < length; i++) {
        if (value[i] < '0' || value[i] > '9') {
            return false;
        }
        digits[i] = value[i] - '0';
    }
    return true;
}

static int calculate_weighted_sum(const int *digits, const int *weights, size_t count)
{
    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        sum += digits[i] * weights[i];
    }
    return sum;
}

static bool check_eik(const int *digits, int check_digit, const int *weights_first,
                      const int *weights_second, size_t count)
{
    int remainder = calculate_weighted_sum(digits, weights_first, count) % 11;

    if (remainder == 10) {
        remainder = calculate_weighted_sum(digits, weights_second, count) % 11;
        if (remainder == 10) {
            remainder = 0;
        }
    }

    return remainder == check_digit;
}

static bool validate_eik9_digits(const int *digits)
{
    int check_digit = digits[EIK9_LENGTH - 1];

    return check_eik(digits, check_digit, EIK9_WEIGHTS_FIRST, EIK9_WEIGHTS_SECOND,
                     EIK9_WEIGHTS_COUNT);
}

static bool validate_eik13_digits(const int *digits)
{
    if (!validate_eik9_digits(digits)) {
        return false;
    }

    const int *part2 = &digits[EIK13_PART_OFFSET];
    int check_digit = digits[EIK13_LENGTH - 1];

    return check_eik(part2, check_digit, EIK13_WEIGHTS_FIRST, EIK13_WEIGHTS_SECOND,
                     EIK13_WEIGHTS_COUNT);
}

bool bg_eik_is_valid(const char *value, size_t length)
{
    int digits[EIK13_LENGTH];

    if (value == NULL) {
        return false;
    }
    if (length != EIK9_LENGTH && length != EIK13_LENGTH) {
        return false;
    }
    if (!extract_digits(value, length, digits)) {
        return false;
    }

    if (length == EIK9_LENGTH) {
        return validate_eik9_digits(digits);
    }
    return validate_eik13_digits(digits);
}
