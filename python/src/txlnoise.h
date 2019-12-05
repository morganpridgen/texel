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
PyObject *NoiseFade(Noise*, PyObject*, PyObject*);
PyObject *NoiseParams(Noise*, PyObject*, PyObject*);
PyObject *NoisePlay(Noise*, PyObject*, PyObject*);

static PyMethodDef NoiseMethods[] = {
  {"setVol", PyCFunction(NoiseFade), METH_VARARGS | METH_KEYWORDS, "Set the volume of the sound and how long it plays"},
  {"setParams", PyCFunction(NoiseParams), METH_VARARGS | METH_KEYWORDS, "Set the cycle speed and bit depth of the sound"},
  {"play", PyCFunction(NoisePlay), METH_VARARGS | METH_KEYWORDS, "Plays the sound"},
  {NULL}
};

extern PyTypeObject NoiseType;

#endif