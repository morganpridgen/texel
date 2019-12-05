#ifndef txlpytextureh
#define txlpytextureh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

PyObject *loadFont(PyObject*, PyObject*, PyObject*);
PyObject *unloadFont(PyObject*, PyObject*, PyObject*);

#define TEXTUREDEC \
  {"loadFont", (PyCFunction)(void(*)(void))loadFont, METH_VARARGS | METH_KEYWORDS, "Loads a font"},\
  {"unloadFont", (PyCFunction)(void(*)(void))unloadFont, METH_NOARGS, "Unoads the font"}

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
PyObject *TextureRender(Texture*, PyObject*, PyObject*);
PyObject *TextureSetClip(Texture*, PyObject*, PyObject*);
PyObject *TextureSetColorMod(Texture*, PyObject*, PyObject*);
PyObject *TextureSetAlphaMod(Texture*, PyObject*, PyObject*);

static PyMethodDef TextureMethods[] = {
  {"render", PyCFunction(TextureRender), METH_VARARGS | METH_KEYWORDS, "Draw the texture"},
  {"setClip", PyCFunction(TextureSetClip), METH_VARARGS | METH_KEYWORDS, "Set the area of the function that gets rendered"},
  {"setColorMod", PyCFunction(TextureSetColorMod), METH_VARARGS | METH_KEYWORDS, "Set the color mod of the texture"},
  {"setAlphaMod", PyCFunction(TextureSetAlphaMod), METH_VARARGS | METH_KEYWORDS, "Set the alpha mod of the texture"},
  {NULL}
};

extern PyTypeObject TextureType;

#endif