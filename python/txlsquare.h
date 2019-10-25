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

void SquareDealloc(Square*);
PyObject *SquareNew(PyTypeObject*, PyObject*, PyObject*);
int SquareInit(Square*, PyObject*, PyObject*);
PyObject *SquareFreq(Square*, PyObject*);
PyObject *SquareFade(Square*, PyObject*);
PyObject *SquareDuty(Square*, PyObject*);
PyObject *SquarePlay(Square*, PyObject*);

static PyMethodDef SquareMethods[] = {
  {"setFreq", PyCFunction(SquareFreq), METH_VARARGS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(SquareFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"setDuty", PyCFunction(SquareDuty), METH_VARARGS, "Set the duty cycle of the sound."},
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