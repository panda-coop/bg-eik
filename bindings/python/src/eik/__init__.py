# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (C) 2026 PANDA Coop

"""Bulgarian EIK / UIC / BULSTAT (ЕИК) validator."""

from ._module import is_valid_eik as _is_valid_eik

__all__ = ["is_valid_eik"]


def is_valid_eik(value: str) -> bool:
    """Validate a Bulgarian EIK / BULSTAT code.

    Accepts strictly 9 or 13 ASCII digits. No trimming or normalisation is done:
    spaces, a ``BG`` prefix or any other character make the value invalid.
    """
    if not isinstance(value, str):
        return False
    return _is_valid_eik(value)
