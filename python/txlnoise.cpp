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

PyTypeObject NoiseType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Noise",   /* tp_name */
    sizeof(Noise),                                  /* tp_basicsize */
    0,                                              /* tp_itemsize */
    (destructor)NoiseDealloc,                       /* tp_dealloc */
    0,                                              /* tp_print */
    0,                                              /* tp_getattr */
    0,                                              /* tp_setattr */
    0,                                              /* tp_reserved */
    0,                                              /* tp_repr */
    0,                                              /* tp_as_number */
    0,                                              /* tp_as_sequence */
    0,                                              /* tp_as_mapping */
    0,                                              /* tp_hash  */
    0,                                              /* tp_call */
    0,                                              /* tp_str */
    0,                                              /* tp_getattro */
    0,                                              /* tp_setattro */
    0,                                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,       /* tp_flags */
    "White noise",                                  /* tp_doc */
    0,                                              /* tp_traverse */
    0,                                              /* tp_clear */
    0,                                              /* tp_richcompare */
    0,                                              /* tp_weaklistoffset */
    0,                                              /* tp_iter */
    0,                                              /* tp_iternext */
    NoiseMethods,                                   /* tp_methods */
    NoiseMembers,                                   /* tp_members */
    0,                                              /* tp_getset */
    0,                                              /* tp_base */
    0,                                              /* tp_dict */
    0,                                              /* tp_descr_get */
    0,                                              /* tp_descr_set */
    0,                                              /* tp_dictoffset */
    (initproc)NoiseInit,                            /* tp_init */
    0,                                              /* tp_alloc */
    NoiseNew,                                       /* tp_new */
};