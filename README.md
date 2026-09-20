# bg-eik

Validator for the Bulgarian **EIK** (ЕИК, also known as UIC or BULSTAT code).
One implementation in C, shipped as a Python package and an npm package.

| Format    | Who has it                                     | Supported |
| --------- | ---------------------------------------------- | --------- |
| 9 digits  | legal entities, sole traders (ЕТ)              | yes       |
| 13 digits | branches and subdivisions                      | yes       |
| 10 digits | natural persons registered under their EGN     | no, by design |

The input must be strictly 9 or 13 ASCII digits. Nothing is trimmed or normalised:
spaces, a `BG` prefix or any other character make the value invalid.

## Usage

```python
# pip install eik
from eik import is_valid_eik

is_valid_eik("942765371")  # True
```

```js
// npm install @panda-coop/eik
import { isValidEik } from '@panda-coop/eik';

isValidEik('942765371'); // true
```

```c
#include "bg_eik.h"

bg_eik_is_valid("942765371", 9); /* true */
```

## Repository layout

```
core/            C implementation, no dependencies, no allocations
bindings/js/     npm package: the core compiled to wasm and inlined as base64
bindings/python/ PyPI package: CPython extension on the stable ABI (abi3)
test-vectors/    shared test cases, every binding runs all of them
```

## Development

Requires [Task](https://taskfile.dev), a C compiler, `clang` + `lld` (wasm),
`clang-format`, Node 18+ and Python 3.9+.

```sh
task            # list tasks
task test       # format check + core, js and python tests
task format     # format C sources
```

Python tasks install into the active interpreter, so activate a virtualenv first.

When changing the algorithm, add cases to `test-vectors/eik.json` instead of
writing per-language tests. That file is the contract between implementations.

See [CONTRIBUTING.md](CONTRIBUTING.md) for the full contribution guidelines.

## License

[GPL-3.0-or-later](LICENSE). Copyright (C) 2026 PANDA Coop.
