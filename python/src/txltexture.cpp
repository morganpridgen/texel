#include "txltexture.h"
#include "txlcolor.h"

PyObject *loadFont(PyObject *self, PyObject *args, PyObject *kwds) {
  char *path;
  char *kwlist[] = {"path", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist, &path)) return nullptr;
  if (!TXL_LoadFont(path)) {
    PyErr_SetString(PyExc_OSError, "Error loading font");
    return nullptr;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *unloadFont(PyObject *self, PyObject *args, PyObject *kwds) {
  TXL_UnloadFont();
  Py_INCREF(Py_None);
  return Py_None;
}

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
  int isText = 0;
  int w = -1, h = -1;
  char *kwlist[] = {"path", "w", "h", "isText", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s|ii$p", kwlist, &path, &w, &h, &isText)) return -1;
  if (!isText) {
    if (!self->tex.load(path, w, h)) {
      PyErr_SetString(PyExc_OSError, "Error loading texture");
      return -1;
    }
  } else {
    TXL_RenderText(&self->tex, path, 1.0f, 1.0f, 1.0f);
    w = self->tex.width(), h = self->tex.height();
  }
  self->tex.setClip(0, w, 0, h);
  return 0;
}

PyObject *TextureRender(Texture *self, PyObject *args, PyObject *kwds) {
  float x, y, w = 1.0f, h = 1.0f, r = 0.0f;
  char *kwlist[] = {"x", "y", "w", "h", "r", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "ff|fff", kwlist, &x, &y, &w, &h, &r)) return nullptr;
  self->tex.render(x, y, w, h, r * (180.0f / 3.141593f));
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TextureSetClip(Texture *self, PyObject *args, PyObject *kwds) {
  int x, y, w, h;
  char *kwlist[] = {"x", "y", "w", "h", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "iiii", kwlist, &x, &y, &w, &h)) return nullptr;
  self->tex.setClip(x, x + w, y, y + h);
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TextureSetColorMod(Texture *self, PyObject *args, PyObject *kwds) {
  Color *color;
  char *kwlist[] = {"color", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!", kwlist, &ColorType, &color)) return nullptr;
  self->tex.setColorMod(color->r, color->g, color->b, color->a);
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *TextureSetAlphaMod(Texture *self, PyObject *args, PyObject *kwds) {
  float a = 1.0f;
  char *kwlist[] = {"a", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|f", kwlist, &a)) return nullptr;
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