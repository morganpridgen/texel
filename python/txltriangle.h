#ifndef txlpytriangleh
#define txlpytriangleh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Triangle {
  PyObject_HEAD
  TXL_Triangle snd;
};

static PyMemberDef TriangleMembers[] = {
  {NULL}
};

void TriangleDealloc(Triangle*);
PyObject *TriangleNew(PyTypeObject*, PyObject*, PyObject*);
int TriangleInit(Triangle*, PyObject*, PyObject*);
PyObject *TriangleFreq(Triangle*, PyObject*);
PyObject *TriangleFade(Triangle*, PyObject*);
PyObject *TrianglePlay(Triangle*, PyObject*);

static PyMethodDef TriangleMethods[] = {
  {"setFreq", PyCFunction(TriangleFreq), METH_VARARGS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(TriangleFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"play", PyCFunction(TrianglePlay), METH_VARARGS, "Plays the sound"},
  {NULL}
};

static PyTypeObject TriangleType = {
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

#endif