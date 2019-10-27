#ifndef txlpynoiseh
#define txlpynoiseh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Noise {
  PyObject_HEAD
  TXL_Noise snd;
};

static PyMemberDef NoiseMembers[] = {
  {NULL}
};

void NoiseDealloc(Noise*);
PyObject *NoiseNew(PyTypeObject*, PyObject*, PyObject*);
int NoiseInit(Noise*, PyObject*, PyObject*);
PyObject *NoiseFade(Noise*, PyObject*);
PyObject *NoiseParams(Noise*, PyObject*);
PyObject *NoisePlay(Noise*, PyObject*);

static PyMethodDef NoiseMethods[] = {
  {"setVol", PyCFunction(NoiseFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"setParams", PyCFunction(NoiseParams), METH_VARARGS, "Set the cycle speed and bit depth of the sound"},
  {"play", PyCFunction(NoisePlay), METH_VARARGS, "Plays the sound"},
  {NULL}
};

extern PyTypeObject NoiseType;

#endif