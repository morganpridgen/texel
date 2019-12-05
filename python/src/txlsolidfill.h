#ifndef txlpysolidfillh
#define txlpysolidfillh

#include <Python.h>
#include <structmember.h>

PyObject *drawRect(PyObject*, PyObject*, PyObject*);

#define SOLIDFILLDEC \
  {"drawRect", (PyCFunction)(void(*)(void))drawRect, METH_VARARGS | METH_KEYWORDS, "Draws a rectangle on the screen"}

#endif