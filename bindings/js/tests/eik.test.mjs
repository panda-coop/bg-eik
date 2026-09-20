// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 PANDA Coop

import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { test } from 'node:test';

import { isValidEik } from '../dist/index.js';

const vectors = JSON.parse(
    readFileSync(new URL('../../../test-vectors/eik.json', import.meta.url), 'utf8'),
);

test('valid vectors', () => {
    for (const { value, note } of vectors.valid) {
        assert.equal(isValidEik(value), true, `${JSON.stringify(value)} (${note})`);
    }
});

test('invalid vectors', () => {
    for (const { value, note } of vectors.invalid) {
        assert.equal(isValidEik(value), false, `${JSON.stringify(value)} (${note})`);
    }
});

test('non-string input is invalid', () => {
    for (const value of [undefined, null, 942765371, {}, []]) {
        assert.equal(isValidEik(value), false);
    }
});

test('very long input is rejected without touching wasm memory', () => {
    assert.equal(isValidEik('1'.repeat(10_000)), false);
});
