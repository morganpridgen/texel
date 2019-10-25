#include "txltriangle.h"

void TriangleDealloc(Triangle *self) {
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *TriangleNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Triangle *self;
  self = (Triangle *)type->tp_alloc(type, 0);
  if (self) memset(&(self->snd), 0, sizeof(TXL_Triangle));
  return (PyObject *)self;
}

int TriangleInit(Triangle *self, PyObject *args, PyObject *kwds) {
  self->snd.freq = 440;
  self->snd.vol = 1.0f;
  self->snd.fade = 1.0f;
  return 0;
}

PyObject *TriangleFreq(Triangle *self, PyObject *args) {
  float freq;
  if (!PyArg_ParseTuple(args, "f", &freq)) return nullptr;
  self->snd.freq = freq;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TriangleFade(Triangle *self, PyObject *args) {
  float vol, fade = 1.0f;
  if (!PyArg_ParseTuple(args, "f|f", &vol, &fade)) return nullptr;
  self->snd.vol = vol;
  self->snd.fade = vol / fade;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TrianglePlay(Triangle *self, PyObject *args) {
  int channel = -1;
  if (!PyArg_ParseTuple(args, "|i", &channel)) return nullptr;
  
  if (channel < 0) TXL_PlaySound(self->snd);
  else TXL_SetMChannel(self->snd, channel);
  Py_INCREF(Py_None);
  return Py_None;
}