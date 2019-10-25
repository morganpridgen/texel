#include "txlnoise.h"

void NoiseDealloc(Noise *self) {
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *NoiseNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Noise *self;
  self = (Noise *)type->tp_alloc(type, 0);
  if (self) memset(&(self->snd), 0, sizeof(TXL_Noise));
  return (PyObject *)self;
}

int NoiseInit(Noise *self, PyObject *args, PyObject *kwds) {
  self->snd.vol = 1.0f;
  self->snd.fade = 1.0f;
  self->snd.seed = 0;
  self->snd.cycle = 8;
  self->snd.bit = 0;
  return 0;
}

PyObject *NoiseFade(Noise *self, PyObject *args) {
  float vol, fade = 1.0f;
  if (!PyArg_ParseTuple(args, "f|f", &vol, &fade)) return nullptr;
  self->snd.vol = vol;
  self->snd.fade = vol / fade;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *NoiseParams(Noise *self, PyObject *args) {
  int cycle, bit = 0;
  if (!PyArg_ParseTuple(args, "i|p", &cycle, &bit)) return nullptr;
  self->snd.cycle = cycle;
  self->snd.bit = bit;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *NoisePlay(Noise *self, PyObject *args) {
  int channel = -1;
  if (!PyArg_ParseTuple(args, "|i", &channel)) return nullptr;
  
  if (channel < 0) TXL_PlaySound(self->snd);
  else TXL_SetMChannel(self->snd, channel);
  Py_INCREF(Py_None);
  return Py_None;
}