# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (C) 2026 PANDA Coop

from pathlib import Path

from setuptools import Extension, setup

PACKAGE = Path("src/pandacoop/bg_eik")
CORE = PACKAGE / "_core"

if not (CORE / "src" / "bg_eik.c").exists():
    raise SystemExit("C core is missing. Run `task python:sync` from the repository root first.")

setup(
    ext_modules=[
        Extension(
            "pandacoop.bg_eik._module",
            sources=[str(PACKAGE / "_module.c"), str(CORE / "src" / "bg_eik.c")],
            include_dirs=[str(CORE / "include")],
            py_limited_api=True,
        )
    ],
    options={"bdist_wheel": {"py_limited_api": "cp39"}},
)
