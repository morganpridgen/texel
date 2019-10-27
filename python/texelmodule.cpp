#include <Python.h>
#include <structmember.h>

#include <TEXEL/texel.h>

#include "txlsquare.h"
#include "txlnoise.h"
#include "txltriangle.h"
#include "txlsawtooth.h"
#include "txldisplay.h"
#include "txlsolidfill.h"
#include "txlcolor.h"

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
  SOLIDFILLDEC,
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
  
  if (PyType_Ready(&NoiseType) < 0) return nullptr;
  PyModule_AddObject(m, "Noise", (PyObject *)&NoiseType);
  
  if (PyType_Ready(&TriangleType) < 0) return nullptr;
  PyModule_AddObject(m, "Triangle", (PyObject *)&TriangleType);
  
  if (PyType_Ready(&SawtoothType) < 0) return nullptr;
  PyModule_AddObject(m, "Sawtooth", (PyObject *)&SawtoothType);
  
  if (PyType_Ready(&DisplayType) < 0) return nullptr;
  PyModule_AddObject(m, "Display", (PyObject *)&DisplayType);
  
  if (PyType_Ready(&ColorType) < 0) return nullptr;
  PyModule_AddObject(m, "Color", (PyObject *)&ColorType);
  
  return m;
}