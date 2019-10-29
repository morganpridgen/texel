#ifndef txlpytextureh
#define txlpytextureh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Texture {
  PyObject_HEAD
  TXL_Texture tex;
};

static PyMemberDef TextureMembers[] = {
  {NULL}
};

void TextureDealloc(Texture*);
PyObject *TextureNew(PyTypeObject*, PyObject*, PyObject*);
int TextureInit(Texture*, PyObject*, PyObject*);
PyObject *TextureRender(Texture*, PyObject*);
PyObject *TextureSetClip(Texture*, PyObject*);
PyObject *TextureSetColorMod(Texture*, PyObject*);
PyObject *TextureSetAlphaMod(Texture*, PyObject*);

static PyMethodDef TextureMethods[] = {
  {"render", PyCFunction(TextureRender), METH_VARARGS, "Draw the texture"},
  {"setClip", PyCFunction(TextureSetClip), METH_VARARGS, "Set the area of the function that gets rendered"},
  {"setColorMod", PyCFunction(TextureSetColorMod), METH_VARARGS, "Set the color mod of the texture"},
  {"setAlphaMod", PyCFunction(TextureSetAlphaMod), METH_VARARGS, "Set the alpha mod of the texture"},
  {NULL}
};

extern PyTypeObject TextureType;

#endif