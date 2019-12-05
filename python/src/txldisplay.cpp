#include "txldisplay.h"
#include "txlcolor.h"

void DisplayDealloc(Display *self) {
  self->disp.end();
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *DisplayNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Display *self;
  self = (Display *)type->tp_alloc(type, 0);
  if (self) memset(&(self->disp), 0, sizeof(TXL_Display));
  return (PyObject *)self;
}

int DisplayInit(Display *self, PyObject *args, PyObject *kwds) {
  char *name;
  char *kwlist[] = {"name", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &name)) return -1;
  if (!self->disp.init(name)) {
    PyErr_SetString(PyExc_OSError, "Error creating window");
    return -1;
  }
  return 0;
}

PyObject *DisplayRefresh(Display *self, PyObject *args, PyObject *kwds) {
  self->disp.refresh();
  PyObject *ok = TXL_Events(&(self->disp)) ? Py_True : Py_False;
  Py_INCREF(ok);
  return ok;
}

PyObject *DisplaySetFill(Display *self, PyObject *args, PyObject *kwds) {
  Color *color;
  char *kwlist[] = {"color", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist, &ColorType, &color)) return nullptr;
  if (color->r < 0.0f || color->r > 1.0f || color->g < 0.0f || color->g > 1.0f || color->b < 0.0f || color->b > 1.0f) {
    PyErr_SetString(PyExc_ValueError, "Color values must be between 0 and 1");
    return nullptr;
  }
  self->disp.setFill(color->r, color->g, color->b);
  Py_INCREF(Py_None);
  return Py_None;
}

PyTypeObject DisplayType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Display",  /* tp_name */
    sizeof(Display),                                 /* tp_basicsize */
    0,                                               /* tp_itemsize */
    (destructor)DisplayDealloc,                      /* tp_dealloc */
    0,                                               /* tp_print */
    0,                                               /* tp_getattr */
    0,                                               /* tp_setattr */
    0,                                               /* tp_reserved */
    0,                                               /* tp_repr */
    0,                                               /* tp_as_number */
    0,                                               /* tp_as_sequence */
    0,                                               /* tp_as_mapping */
    0,                                               /* tp_hash  */
    0,                                               /* tp_call */
    0,                                               /* tp_str */
    0,                                               /* tp_getattro */
    0,                                               /* tp_setattro */
    0,                                               /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
    "Display window",                                /* tp_doc */
    0,                                               /* tp_traverse */
    0,                                               /* tp_clear */
    0,                                               /* tp_richcompare */
    0,                                               /* tp_weaklistoffset */
    0,                                               /* tp_iter */
    0,                                               /* tp_iternext */
    DisplayMethods,                                  /* tp_methods */
    DisplayMembers,                                  /* tp_members */
    0,                                               /* tp_getset */
    0,                                               /* tp_base */
    0,                                               /* tp_dict */
    0,                                               /* tp_descr_get */
    0,                                               /* tp_descr_set */
    0,                                               /* tp_dictoffset */
    (initproc)DisplayInit,                           /* tp_init */
    0,                                               /* tp_alloc */
    DisplayNew,                                      /* tp_new */
};