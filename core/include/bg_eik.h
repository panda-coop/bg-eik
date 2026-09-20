/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (C) 2026 PANDA Coop */

#ifndef BG_EIK_H
#define BG_EIK_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Validates a Bulgarian EIK / BULSTAT code (ЕИК).
 *
 * Supported formats:
 *   - 9 digits:  legal entities and sole traders
 *   - 13 digits: branches and subdivisions (a valid 9-digit EIK + 4 more digits)
 *
 * 10-digit codes (natural persons registered under their EGN) are
 * intentionally not supported.
 *
 * @param value   code string, does not have to be NUL-terminated
 * @param length  string length in bytes
 * @return true if the string consists of digits only and all check digits match
 */
bool bg_eik_is_valid(const char *value, size_t length);

#ifdef __cplusplus
}
#endif

#endif /* BG_EIK_H */
