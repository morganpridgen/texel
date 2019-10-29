#ifndef txlpysawtoothh
#define txlpysawtoothh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

struct Sawtooth {
  PyObject_HEAD
  TXL_Sawtooth snd;
};

static PyMemberDef SawtoothMembers[] = {
  {NULL}
};

void SawtoothDealloc(Sawtooth*);
PyObject *SawtoothNew(PyTypeObject*, PyObject*, PyObject*);
int SawtoothInit(Sawtooth*, PyObject*, PyObject*);
PyObject *SawtoothFreq(Sawtooth*, PyObject*);
PyObject *SawtoothFade(Sawtooth*, PyObject*);
PyObject *SawtoothPlay(Sawtooth*, PyObject*);

static PyMethodDef SawtoothMethods[] = {
  {"setFreq", PyCFunction(SawtoothFreq), METH_VARARGS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(SawtoothFade), METH_VARARGS, "Set the volume of the sound and how long it plays"},
  {"play", PyCFunction(SawtoothPlay), METH_VARARGS, "Plays the sound"},
  {NULL}
};

extern PyTypeObject SawtoothType;

#endif