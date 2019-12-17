#ifndef txlpysolidfillh
#define txlpysolidfillh

#include <Python.h>
#include <structmember.h>

PyObject *drawRect(PyObject*, PyObject*, PyObject*);
PyObject *drawTri(PyObject*, PyObject*, PyObject*);

#define SOLIDFILLDEC \
  {"drawRect", (PyCFunction)(void(*)(void))drawRect, METH_VARARGS | METH_KEYWORDS, "Draws a rectangle on the screen"},\
  {"drawTri", (PyCFunction)(void(*)(void))drawTri, METH_VARARGS | METH_KEYWORDS, "Draws a triangle on the screen"}

#endif