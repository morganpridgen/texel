#include "txlsolidfill.h"
#include "txlcolor.h"

#include <TEXEL/texel.h>

PyObject *drawRect(PyObject *self, PyObject *args) {
  float x, y, w, h;
  Color *color;
  if (!PyArg_ParseTuple(args, "ffffO!", &x, &y, &w, &h, &ColorType, &color)) return nullptr;
  TXL_RenderQuad(x, y, w, h, {color->r, color->g, color->b, color->a});
  Py_INCREF(Py_None);
  return Py_None;
}