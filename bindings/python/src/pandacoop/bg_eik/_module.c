/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright (C) 2026 PANDA Coop */

/* CPython glue around the C core. Uses the stable ABI (abi3). */

#define PY_SSIZE_T_CLEAN
#define Py_LIMITED_API 0x03090000
#include <Python.h>

#include "bg_eik.h"

static PyObject *py_is_valid_eik(PyObject *self, PyObject *args)
{
    const char *value;
    Py_ssize_t length;

    (void)self;

    if (!PyArg_ParseTuple(args, "s#", &value, &length)) {
        return NULL;
    }

    return PyBool_FromLong(bg_eik_is_valid(value, (size_t)length));
}

static PyMethodDef module_methods[] = {
    {"is_valid_eik", py_is_valid_eik, METH_VARARGS, "Validate raw EIK bytes."},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef module_definition = {
    PyModuleDef_HEAD_INIT, "_module", NULL, -1, module_methods, NULL, NULL, NULL, NULL,
};

PyMODINIT_FUNC PyInit__module(void)
{
    return PyModule_Create(&module_definition);
}
