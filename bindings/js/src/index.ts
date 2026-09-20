// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (C) 2026 PANDA Coop

import { WASM_BASE64 } from './wasm-bytes.js';

interface CoreExports {
    memory: WebAssembly.Memory;
    bg_eik_buffer(): number;
    bg_eik_buffer_size(): number;
    bg_eik_check(length: number): number;
}

const decodeBase64 = (base64: string): Uint8Array<ArrayBuffer> => {
    const binary = atob(base64);
    const bytes = new Uint8Array(binary.length);

    for (let i = 0; i < binary.length; i++) {
        bytes[i] = binary.charCodeAt(i);
    }
    return bytes;
};

// The module is a few hundred bytes, so synchronous compilation is fine
// both in Node and on the browser main thread.
const wasmModule = new WebAssembly.Module(decodeBase64(WASM_BASE64));
const core = new WebAssembly.Instance(wasmModule).exports as unknown as CoreExports;

const bufferOffset = core.bg_eik_buffer();
const bufferSize = core.bg_eik_buffer_size();
const buffer = new Uint8Array(core.memory.buffer, bufferOffset, bufferSize);

/**
 * Validates a Bulgarian EIK / BULSTAT code (ЕИК).
 *
 * Accepts strictly 9 or 13 ASCII digits. No trimming or normalisation is done:
 * spaces, a "BG" prefix or any other character make the value invalid.
 */
export const isValidEik = (value: string): boolean => {
    if (typeof value !== 'string' || value.length > bufferSize) {
        return false;
    }

    for (let i = 0; i < value.length; i++) {
        const code = value.charCodeAt(i);

        // Anything outside ASCII cannot be a digit; do not let it wrap around in a byte.
        if (code > 0x7f) {
            return false;
        }
        buffer[i] = code;
    }

    return core.bg_eik_check(value.length) === 1;
};
