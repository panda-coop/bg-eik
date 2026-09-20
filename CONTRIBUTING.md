# Contributing

## Development setup

Requires [Task](https://taskfile.dev), a C compiler, `clang` + `lld` (wasm),
`clang-format`, Node 18+ and Python 3.9+.

```sh
task            # list tasks
task test       # format check + core, js and python test suites
```

Python tasks install into the active interpreter — activate a virtualenv first.

## The test-vector contract

`test-vectors/eik.json` is the single source of truth for the validation
algorithm, and every binding runs all of its cases. When changing the
algorithm, add cases there — never as per-language tests. Per-language tests
exist only for binding-specific behavior (non-string input, embedded NUL
bytes, wasm buffer limits).

## Formatting

C sources are formatted with clang-format; CI fails on unformatted code.

```sh
task format
```

## Commits and pull requests

- Conventional commit messages (`feat:`, `fix:`, `docs:`, `ci:`, ...),
  imperative mood, no emoji.
- Open pull requests against `main`; CI must be green.
- Keep changes small and scoped. Unrelated refactoring belongs in its own PR.

## Licensing

bg-eik is licensed under GPL-3.0-or-later. Contributions are accepted under
the same terms (inbound = outbound); there is no CLA. New source files carry
the SPDX header used throughout the repository:

```c
/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (C) 2026 PANDA Coop */
```
