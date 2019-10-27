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

PyTypeObject TriangleType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Triangle",  /* tp_name */
    sizeof(Triangle),                                 /* tp_basicsize */
    0,                                                /* tp_itemsize */
    (destructor)TriangleDealloc,                      /* tp_dealloc */
    0,                                                /* tp_print */
    0,                                                /* tp_getattr */
    0,                                                /* tp_setattr */
    0,                                                /* tp_reserved */
    0,                                                /* tp_repr */
    0,                                                /* tp_as_number */
    0,                                                /* tp_as_sequence */
    0,                                                /* tp_as_mapping */
    0,                                                /* tp_hash  */
    0,                                                /* tp_call */
    0,                                                /* tp_str */
    0,                                                /* tp_getattro */
    0,                                                /* tp_setattro */
    0,                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,         /* tp_flags */
    "Triangle wave",                                  /* tp_doc */
    0,                                                /* tp_traverse */
    0,                                                /* tp_clear */
    0,                                                /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    0,                                                /* tp_iter */
    0,                                                /* tp_iternext */
    TriangleMethods,                                  /* tp_methods */
    TriangleMembers,                                  /* tp_members */
    0,                                                /* tp_getset */
    0,                                                /* tp_base */
    0,                                                /* tp_dict */
    0,                                                /* tp_descr_get */
    0,                                                /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    (initproc)TriangleInit,                           /* tp_init */
    0,                                                /* tp_alloc */
    TriangleNew,                                      /* tp_new */
};