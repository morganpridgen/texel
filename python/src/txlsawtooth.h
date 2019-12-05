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
PyObject *SawtoothFreq(Sawtooth*, PyObject*, PyObject*);
PyObject *SawtoothFade(Sawtooth*, PyObject*, PyObject*);
PyObject *SawtoothPlay(Sawtooth*, PyObject*, PyObject*);

static PyMethodDef SawtoothMethods[] = {
  {"setFreq", PyCFunction(SawtoothFreq), METH_VARARGS | METH_KEYWORDS, "Set the frequency of the sound"},
  {"setVol", PyCFunction(SawtoothFade), METH_VARARGS | METH_KEYWORDS, "Set the volume of the sound and how long it plays"},
  {"play", PyCFunction(SawtoothPlay), METH_VARARGS | METH_KEYWORDS, "Plays the sound"},
  {NULL}
};

extern PyTypeObject SawtoothType;

#endif