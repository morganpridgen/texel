#include "txlcontroller.h"

void ControllerDealloc(Controller *self) {
  delete self->ctrl;
  Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject *ControllerNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
  Controller *self;
  self = (Controller *)type->tp_alloc(type, 0);
  if (self) self->ctrl = nullptr;
  return (PyObject *)self;
}

int ControllerInit(Controller *self, PyObject *args, PyObject *kwds) {
  self->ctrl = new TXL_Controller;
  if (!self->ctrl->init()) {
    delete self->ctrl;
    self->ctrl = new TXL_Keyboard;
    self->ctrl->init();
  }
  return 0;
}

PyObject *ControllerUpdate(Controller *self, PyObject *args, PyObject *kwds) {
  TXL_ManageController(self->ctrl);
  Py_INCREF(Py_None);
  return Py_None;
}

PyObject *ControllerIsKeyboard(Controller *self, PyObject *args, PyObject *kwds) {
  PyObject *ok = self->ctrl->isKeyboard() ? Py_True : Py_False;
  Py_INCREF(ok);
  return ok;
}

PyObject *ControllerPress(Controller *self, PyObject *args, PyObject *kwds) {
  int button = 0;
  char *kwlist[] = {"b", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &button)) return nullptr;
  PyObject *ok = self->ctrl->buttonPress((TXL_CtrlButton)button) ? Py_True : Py_False;
  Py_INCREF(ok);
  return ok;
}

PyObject *ControllerClick(Controller *self, PyObject *args, PyObject *kwds) {
  int button = 0;
  char *kwlist[] = {"b", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &button)) return nullptr;
  PyObject *ok = self->ctrl->buttonClick((TXL_CtrlButton)button) ? Py_True : Py_False;
  Py_INCREF(ok);
  return ok;
}

PyObject *ControllerRelease(Controller *self, PyObject *args, PyObject *kwds) {
  int button = 0;
  char *kwlist[] = {"b", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "i", kwlist, &button)) return nullptr;
  PyObject *ok = self->ctrl->buttonRelease((TXL_CtrlButton)button) ? Py_True : Py_False;
  Py_INCREF(ok);
  return ok;
}

PyObject *ControllerJoyX(Controller *self, PyObject *args, PyObject *kwds) {
  return Py_BuildValue("f", self->ctrl->leftJoyX());
}

PyObject *ControllerJoyY(Controller *self, PyObject *args, PyObject *kwds) {
  return Py_BuildValue("f", self->ctrl->leftJoyY());
}

PyObject *ControllerMouseX(Controller *self, PyObject *args, PyObject *kwds) {
  return Py_BuildValue("f", self->ctrl->mouseX());
}

PyObject *ControllerMouseY(Controller *self, PyObject *args, PyObject *kwds) {
  return Py_BuildValue("f", self->ctrl->mouseY());
}

PyObject *ControllerId(Controller *self, PyObject *args, PyObject *kwds) {
  return Py_BuildValue("i", self->ctrl->getId());
}

PyObject *ControllerRumble(Controller *self, PyObject *args, PyObject *kwds) {
  float power, time;
  char *kwlist[] = {"power", "time", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "ff", kwlist, &power, &time)) return nullptr;
  self->ctrl->rumble(power, int(time * 1000));
  Py_INCREF(Py_None);
  return Py_None;
}

PyTypeObject ControllerType = {
    PyVarObject_HEAD_INIT(NULL, 0) "texel.Controller",  /* tp_name */
    sizeof(Controller),                                 /* tp_basicsize */
    0,                                                  /* tp_itemsize */
    (destructor)ControllerDealloc,                      /* tp_dealloc */
    0,                                                  /* tp_print */
    0,                                                  /* tp_getattr */
    0,                                                  /* tp_setattr */
    0,                                                  /* tp_reserved */
    0,                                                  /* tp_repr */
    0,                                                  /* tp_as_number */
    0,                                                  /* tp_as_sequence */
    0,                                                  /* tp_as_mapping */
    0,                                                  /* tp_hash  */
    0,                                                  /* tp_call */
    0,                                                  /* tp_str */
    0,                                                  /* tp_getattro */
    0,                                                  /* tp_setattro */
    0,                                                  /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /* tp_flags */
    "Controller",                                       /* tp_doc */
    0,                                                  /* tp_traverse */
    0,                                                  /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,                                                  /* tp_weaklistoffset */
    0,                                                  /* tp_iter */
    0,                                                  /* tp_iternext */
    ControllerMethods,                                  /* tp_methods */
    ControllerMembers,                                  /* tp_members */
    0,                                                  /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    (initproc)ControllerInit,                           /* tp_init */
    0,                                                  /* tp_alloc */
    ControllerNew,                                      /* tp_new */
};