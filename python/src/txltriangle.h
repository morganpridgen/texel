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
PyObject *TriangleFreq(Triangle*, PyObject*, PyObject*);
PyObject *TriangleFade(Triangle*, PyObject*, PyObject*);
PyObject *TrianglePlay(Triangle*, PyObject*, PyObject*);

static PyMethodDef TriangleMethods[] = {
  {"setFreq", PyCFunction(TriangleFreq), METH_VARARGS | METH_KEYWORDS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(TriangleFade), METH_VARARGS | METH_KEYWORDS, "Set the volume of the sound and how long it plays"},
  {"play", PyCFunction(TrianglePlay), METH_VARARGS | METH_KEYWORDS, "Plays the sound"},
  {NULL}
};

extern PyTypeObject TriangleType;

#endif