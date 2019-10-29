#ifndef txlpycolorh
#define txlpycolorh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Color {
  PyObject_HEAD
  float r, g, b, a;
};

static PyMemberDef ColorMembers[] = {
  {"r", T_FLOAT, offsetof(Color, r), 0, "Red portion of color"},
  {"g", T_FLOAT, offsetof(Color, g), 0, "Green portion of color"},
  {"b", T_FLOAT, offsetof(Color, b), 0, "Blue portion of color"},
  {"a", T_FLOAT, offsetof(Color, a), 0, "Opacity of color"},
  {NULL}
};

void ColorDealloc(Color*);
PyObject *ColorNew(PyTypeObject*, PyObject*, PyObject*);
int ColorInit(Color*, PyObject*, PyObject*);

static PyMethodDef ColorMethods[] = {
  {NULL}
};

extern PyTypeObject ColorType;

#endif