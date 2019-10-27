#ifndef txlpysolidfillh
#define txlpysolidfillh

#include <Python.h>
#include <structmember.h>

PyObject *drawRect(PyObject *, PyObject *);

#define SOLIDFILLDEC \
  {"drawRect", drawRect, METH_VARARGS, "Draws a rectangle on the screen"}

#endif