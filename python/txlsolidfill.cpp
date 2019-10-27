#include "txlsolidfill.h"
#include "txlcolor.h"

#include <TEXEL/texel.h>

PyObject *drawRect(PyObject *self, PyObject *args) {
  float x, y, w, h;
  Color color;
  if (!PyArg_ParseTuple(args, "ffffO!", &x, &y, &w, &h, &ColorType, (PyObject *)&color)) return nullptr;
  printf("%.2ef %.2ef %.2ef %.2ef\n", color.r, color.g, color.b, color.a);
  TXL_RenderQuad(x, y, w, h, {color.r, color.g, color.b, color.a});
  Py_INCREF(Py_None);
  return Py_None;
}