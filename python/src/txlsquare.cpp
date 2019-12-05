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

PyObject *SquareFreq(Square *self, PyObject *args, PyObject *kwds) {
  float freq;
  char *kwlist[] = {"freq", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "f", kwlist, &freq)) return nullptr;
  self->snd.freq = freq;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *SquareFade(Square *self, PyObject *args, PyObject *kwds) {
  float vol, fade = 1.0f;
  char *kwlist[] = {"vol", "fade", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "f|f", kwlist, &vol, &fade)) return nullptr;
  self->snd.vol = vol;
  self->snd.fade = vol / fade;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *SquareDuty(Square *self, PyObject *args, PyObject *kwds) {
  int duty;
  char *kwlist[] = {"duty", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &duty)) return nullptr;
  if (duty % 4 != duty) {
    PyErr_SetString(PyExc_ValueError, "Duty cycle must be 0, 1, 2, or 3");
    return nullptr;
  }
  self->snd.duty = duty;
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *SquarePlay(Square *self, PyObject *args, PyObject *kwds) {
  int channel = -1;
  char *kwlist[] = {"channel", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &channel)) return nullptr;
  if (channel < 0) TXL_PlaySound(self->snd);
  else TXL_SetMChannel(self->snd, channel);
  Py_INCREF(Py_None);
  return Py_None;
}

PyTypeObject SquareType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Square",   /* tp_name */
    sizeof(Square),                                 /* tp_basicsize */
    0,                                              /* tp_itemsize */
    (destructor)SquareDealloc,                      /* tp_dealloc */
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
    "Square wave",                                  /* tp_doc */
    0,                                              /* tp_traverse */
    0,                                              /* tp_clear */
    0,                                              /* tp_richcompare */
    0,                                              /* tp_weaklistoffset */
    0,                                              /* tp_iter */
    0,                                              /* tp_iternext */
    SquareMethods,                                  /* tp_methods */
    SquareMembers,                                  /* tp_members */
    0,                                              /* tp_getset */
    0,                                              /* tp_base */
    0,                                              /* tp_dict */
    0,                                              /* tp_descr_get */
    0,                                              /* tp_descr_set */
    0,                                              /* tp_dictoffset */
    (initproc)SquareInit,                           /* tp_init */
    0,                                              /* tp_alloc */
    SquareNew,                                      /* tp_new */
};