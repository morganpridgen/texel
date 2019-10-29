#ifndef txlpydisplayh
#define txlpydisplayh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Display {
  PyObject_HEAD
  TXL_Display disp;
};

static PyMemberDef DisplayMembers[] = {
  {NULL}
};

void DisplayDealloc(Display*);
PyObject *DisplayNew(PyTypeObject*, PyObject*, PyObject*);
int DisplayInit(Display*, PyObject*, PyObject*);
PyObject *DisplayRefresh(Display*, PyObject*);
PyObject *DisplaySetFill(Display*, PyObject*);

static PyMethodDef DisplayMethods[] = {
  {"refresh", PyCFunction(DisplayRefresh), METH_NOARGS, "Redraw the window"},
  {"setFill", PyCFunction(DisplaySetFill), METH_VARARGS, "Set the redraw color"},
  {NULL}
};

extern PyTypeObject DisplayType;

#endif