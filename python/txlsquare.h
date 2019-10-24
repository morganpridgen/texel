#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Square {
  PyObject_HEAD
  TXL_Square snd;
};

static PyMemberDef SquareMembers[] = {
  {NULL}
};

static void SquareDealloc(Square *self) {
  Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *SquareNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Square *self;
  self = (Square *)type->tp_alloc(type, 0);
  if (self) memset(&(self->snd), 0, sizeof(TXL_Square));
  return (PyObject *)self;
}

static int SquareInit(Square *self, PyObject *args, PyObject *kwds) {
  return 0;
}

static PyObject *SquareFreq(Square *self, PyObject *args) {
  float freq;
  if (!PyArg_ParseTuple(args, "f", &freq)) return nullptr;
  self->snd.freq = freq;
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *SquareFade(Square *self, PyObject *args) {
  float vol, fade = 1.0f;
  if (!PyArg_ParseTuple(args, "f|f", &vol, &fade)) return nullptr;
  self->snd.vol = vol;
  self->snd.fade = vol / fade;
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *SquarePlay(Square *self, PyObject *args) {
  int channel = -1;
  if (!PyArg_ParseTuple(args, "|i", &channel)) return nullptr;
  
  if (channel < 0) TXL_PlaySound(self->snd);
  else TXL_SetMChannel(self->snd, channel);
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMethodDef SquareMethods[] = {
  {"setFreq", PyCFunction(SquareFreq), METH_VARARGS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(SquareFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"play", PyCFunction(SquarePlay), METH_VARARGS, "Plays the sound"},
  {NULL}
};

static PyTypeObject SquareType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.square",  /* tp_name */
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