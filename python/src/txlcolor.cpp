#include "txlcolor.h"

void ColorDealloc(Color *self) {
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *ColorNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Color *self;
  self = (Color *)type->tp_alloc(type, 0);
  if (self) self->r = 0.0f, self ->g = 0.0f, self->b = 0.0f, self->a = 1.0f;
  return (PyObject *)self;
}

int ColorInit(Color *self, PyObject *args, PyObject *kwds) {
  self->r = 0.0f, self ->g = 0.0f, self->b = 0.0f, self->a = 1.0f;
  if (!PyArg_ParseTuple(args, "fff|f", &(self->r), &(self->g), &(self->b), &(self->a))) return -1;
  return 0;
}

PyTypeObject ColorType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Color",  /* tp_name */
    sizeof(Color),                                 /* tp_basicsize */
    0,                                             /* tp_itemsize */
    (destructor)ColorDealloc,                      /* tp_dealloc */
    0,                                             /* tp_print */
    0,                                             /* tp_getattr */
    0,                                             /* tp_setattr */
    0,                                             /* tp_reserved */
    0,                                             /* tp_repr */
    0,                                             /* tp_as_number */
    0,                                             /* tp_as_sequence */
    0,                                             /* tp_as_mapping */
    0,                                             /* tp_hash  */
    0,                                             /* tp_call */
    0,                                             /* tp_str */
    0,                                             /* tp_getattro */
    0,                                             /* tp_setattro */
    0,                                             /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,      /* tp_flags */
    "Color",                                       /* tp_doc */
    0,                                             /* tp_traverse */
    0,                                             /* tp_clear */
    0,                                             /* tp_richcompare */
    0,                                             /* tp_weaklistoffset */
    0,                                             /* tp_iter */
    0,                                             /* tp_iternext */
    ColorMethods,                                  /* tp_methods */
    ColorMembers,                                  /* tp_members */
    0,                                             /* tp_getset */
    0,                                             /* tp_base */
    0,                                             /* tp_dict */
    0,                                             /* tp_descr_get */
    0,                                             /* tp_descr_set */
    0,                                             /* tp_dictoffset */
    (initproc)ColorInit,                           /* tp_init */
    0,                                             /* tp_alloc */
    ColorNew,                                      /* tp_new */
};