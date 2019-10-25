#ifndef txlpysawtoothh
#define txlpysawtoothh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Sawtooth {
  PyObject_HEAD
  TXL_Sawtooth snd;
};

static PyMemberDef SawtoothMembers[] = {
  {NULL}
};

void SawtoothDealloc(Sawtooth*);
PyObject *SawtoothNew(PyTypeObject*, PyObject*, PyObject*);
int SawtoothInit(Sawtooth*, PyObject*, PyObject*);
PyObject *SawtoothFreq(Sawtooth*, PyObject*);
PyObject *SawtoothFade(Sawtooth*, PyObject*);
PyObject *SawtoothPlay(Sawtooth*, PyObject*);

static PyMethodDef SawtoothMethods[] = {
  {"setFreq", PyCFunction(SawtoothFreq), METH_VARARGS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(SawtoothFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"play", PyCFunction(SawtoothPlay), METH_VARARGS, "Plays the sound"},
  {NULL}
};

static PyTypeObject SawtoothType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Sawtooth",  /* tp_name */
    sizeof(Sawtooth),                                 /* tp_basicsize */
    0,                                                /* tp_itemsize */
    (destructor)SawtoothDealloc,                      /* tp_dealloc */
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
    "Sawtooth wave",                                  /* tp_doc */
    0,                                                /* tp_traverse */
    0,                                                /* tp_clear */
    0,                                                /* tp_richcompare */
    0,                                                /* tp_weaklistoffset */
    0,                                                /* tp_iter */
    0,                                                /* tp_iternext */
    SawtoothMethods,                                  /* tp_methods */
    SawtoothMembers,                                  /* tp_members */
    0,                                                /* tp_getset */
    0,                                                /* tp_base */
    0,                                                /* tp_dict */
    0,                                                /* tp_descr_get */
    0,                                                /* tp_descr_set */
    0,                                                /* tp_dictoffset */
    (initproc)SawtoothInit,                           /* tp_init */
    0,                                                /* tp_alloc */
    SawtoothNew,                                      /* tp_new */
};

#endif