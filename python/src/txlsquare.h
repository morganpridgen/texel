#ifndef txlpysquareh
#define txlpysquareh

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
PyObject *SquareFreq(Square*, PyObject*, PyObject*);
PyObject *SquareFade(Square*, PyObject*, PyObject*);
PyObject *SquareDuty(Square*, PyObject*, PyObject*);
PyObject *SquarePlay(Square*, PyObject*, PyObject*);

static PyMethodDef SquareMethods[] = {
  {"setFreq", PyCFunction(SquareFreq), METH_VARARGS | METH_KEYWORDS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(SquareFade), METH_VARARGS | METH_KEYWORDS, "Set the volume of the sound and how long it plays"},
  {"setDuty", PyCFunction(SquareDuty), METH_VARARGS | METH_KEYWORDS, "Set the duty cycle of the sound."},
  {"play", PyCFunction(SquarePlay), METH_VARARGS | METH_KEYWORDS, "Plays the sound"},
  {NULL}
};

extern PyTypeObject SquareType;

#endif