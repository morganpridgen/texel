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

extern PyTypeObject SquareType;

#endif