#include <Python.h>
#include <structmember.h>

#include <TEXEL/texel.h>

#include "txlsquare.h"

static PyObject *init(PyObject *self, PyObject *args) {
  PyObject *ok = TXL_Init() ? Py_True : Py_False;
  Py_INCREF(ok);
  return ok;
}

static PyObject *end(PyObject *self, PyObject *args) {
  TXL_End();
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef texelMethods[] {
  {"init", init, METH_NOARGS, "Initializes Texel"},
  {"end", end, METH_NOARGS, "Ends Texel"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef texelDef = {
  PyModuleDef_HEAD_INIT,
  "texel",
  "Python implementation of Texel",
  -1,
  texelMethods
};

PyMODINIT_FUNC PyInit_texel() {
  Py_Initialize();
  PyObject *m = PyModule_Create(&texelDef);
  
  if (PyType_Ready(&SquareType) < 0) return nullptr;
  PyModule_AddObject(m, "Square", (PyObject *)&SquareType);
  
  return m;
}