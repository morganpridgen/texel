#include "txltexture.h"
#include "txlcolor.h"

void TextureDealloc(Texture *self) {
  self->tex.free();
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *TextureNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Texture *self;
  self = (Texture *)type->tp_alloc(type, 0);
  if (self) memset(&(self->tex), 0, sizeof(TXL_Texture));
  return (PyObject *)self;
}

int TextureInit(Texture *self, PyObject *args, PyObject *kwds) {
  char *path;
  int w = -1, h = -1;
  if (!PyArg_ParseTuple(args, "s|ii", &path, &w, &h)) return -1;
  if (!self->tex.load(path, w, h)) {
    PyErr_SetString(PyExc_OSError, "Error loading texture");
    return -1;
  }
  return 0;
}

PyObject *TextureRender(Texture *self, PyObject *args) {
  float x, y, w = 1.0f, h = 1.0f, r = 0.0f;
  if (!PyArg_ParseTuple(args, "ff|fff", &x, &y, &w, &h, &r)) return nullptr;
  self->tex.render(x, y, w, h, r * (180 / 3.141593f));
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TextureSetClip(Texture *self, PyObject *args) {
  int x, y, w, h;
  if (!PyArg_ParseTuple(args, "iiii", &x, &y, &w, &h)) return nullptr;
  self->tex.setClip(x, x + w, y, y + h);
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TextureSetColorMod(Texture *self, PyObject *args) {
  Color *color;
  if (!PyArg_ParseTuple(args, "O!", &ColorType, &color)) return nullptr;
  self->tex.setColorMod(color->r, color->g, color->b, color->a);
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TextureSetAlphaMod(Texture *self, PyObject *args) {
  float a = 1.0f;
  if (!PyArg_ParseTuple(args, "|f", &a)) return nullptr;
  self->tex.setColorMod(a);
  Py_INCREF(Py_None);
  return Py_None;
}

PyTypeObject TextureType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Texture",  /* tp_name */
    sizeof(Texture),                                 /* tp_basicsize */
    0,                                               /* tp_itemsize */
    (destructor)TextureDealloc,                      /* tp_dealloc */
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
    "Texture",                                       /* tp_doc */
    0,                                               /* tp_traverse */
    0,                                               /* tp_clear */
    0,                                               /* tp_richcompare */
    0,                                               /* tp_weaklistoffset */
    0,                                               /* tp_iter */
    0,                                               /* tp_iternext */
    TextureMethods,                                  /* tp_methods */
    TextureMembers,                                  /* tp_members */
    0,                                               /* tp_getset */
    0,                                               /* tp_base */
    0,                                               /* tp_dict */
    0,                                               /* tp_descr_get */
    0,                                               /* tp_descr_set */
    0,                                               /* tp_dictoffset */
    (initproc)TextureInit,                           /* tp_init */
    0,                                               /* tp_alloc */
    TextureNew,                                      /* tp_new */
};