#include "txlsquare.h"

void SquareDealloc(Square *self) {
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *SquareNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Square *self;
  self = (Square *)type->tp_alloc(type, 0);
  if (self) memset(&(self->snd), 0, sizeof(TXL_Square));
  return (PyObject *)self;
}

int SquareInit(Square *self, PyObject *args, PyObject *kwds) {
  self->snd.freq = 440;
  self->snd.vol = 1.0f;
  self->snd.fade = 1.0f;
  self->snd.duty = 2;
  return 0;
}

PyObject *SquareFreq(Square *self, PyObject *args) {
  float freq;
  if (!PyArg_ParseTuple(args, "f", &freq)) return nullptr;
  self->snd.freq = freq;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *SquareFade(Square *self, PyObject *args) {
  float vol, fade = 1.0f;
  if (!PyArg_ParseTuple(args, "f|f", &vol, &fade)) return nullptr;
  self->snd.vol = vol;
  self->snd.fade = vol / fade;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *SquareDuty(Square *self, PyObject *args) {
  int duty;
  if (!PyArg_ParseTuple(args, "i", &duty)) return nullptr;
  if (duty % 4 != duty) {
    PyErr_SetString(PyExc_ValueError, "Duty cycle must be 0, 1, 2, or 3");
    return nullptr;
  }
  self->snd.duty = duty;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *SquarePlay(Square *self, PyObject *args) {
  int channel = -1;
  if (!PyArg_ParseTuple(args, "|i", &channel)) return nullptr;
  
  if (channel < 0) TXL_PlaySound(self->snd);
  else TXL_SetMChannel(self->snd, channel);
  Py_INCREF(Py_None);
  return Py_None;
}