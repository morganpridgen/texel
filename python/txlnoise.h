#ifndef txlpynoiseh
#define txlpynoiseh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Noise {
  PyObject_HEAD
  TXL_Noise snd;
};

static PyMemberDef NoiseMembers[] = {
  {NULL}
};

void NoiseDealloc(Noise*);
PyObject *NoiseNew(PyTypeObject*, PyObject*, PyObject*);
int NoiseInit(Noise*, PyObject*, PyObject*);
PyObject *NoiseFade(Noise*, PyObject*);
PyObject *NoiseParams(Noise*, PyObject*);
PyObject *NoisePlay(Noise*, PyObject*);

static PyMethodDef NoiseMethods[] = {
  {"setVol", PyCFunction(NoiseFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"setParams", PyCFunction(NoiseParams), METH_VARARGS, "Set the cycle speed and bit depth of the sound"},
  {"play", PyCFunction(NoisePlay), METH_VARARGS, "Plays the sound"},
  {NULL}
};

static PyTypeObject NoiseType = {
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

#endif