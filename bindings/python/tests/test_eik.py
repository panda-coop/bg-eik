# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (C) 2026 PANDA Coop

import json
from pathlib import Path

import pytest

from pandacoop.bg_eik import is_valid_eik

VECTORS = json.loads(
    (Path(__file__).resolve().parents[3] / "test-vectors" / "eik.json").read_text(encoding="utf-8")
)


@pytest.mark.parametrize("case", VECTORS["valid"], ids=lambda case: case["note"])
def test_valid(case):
    assert is_valid_eik(case["value"]) is True


@pytest.mark.parametrize("case", VECTORS["invalid"], ids=lambda case: case["note"])
def test_invalid(case):
    assert is_valid_eik(case["value"]) is False


@pytest.mark.parametrize("value", [None, 942765371, b"942765371", [], {}])
def test_non_string_input_is_invalid(value):
    assert is_valid_eik(value) is False


def test_embedded_nul_is_invalid():
    assert is_valid_eik("94276537\x00") is False
