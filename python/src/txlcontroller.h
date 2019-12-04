#ifndef txlpycontrollerh
#define txlpycontrollerh

#include <Python.h>
#include <structmember.h>

#include <cstring>

#include <TEXEL/texel.h>

#define CTRLBUTTONDEF \
PyModule_AddIntConstant(m, "CtrlN", CtrlN);\
PyModule_AddIntConstant(m, "CtrlS", CtrlS);\
PyModule_AddIntConstant(m, "CtrlE", CtrlE);\
PyModule_AddIntConstant(m, "CtrlW", CtrlW);\
PyModule_AddIntConstant(m, "CtrlStart", CtrlStart);\
PyModule_AddIntConstant(m, "CtrlSelect", CtrlSelect);\
PyModule_AddIntConstant(m, "CtrlL", CtrlL);\
PyModule_AddIntConstant(m, "CtrlR", CtrlR);\
PyModule_AddIntConstant(m, "CtrlA", CtrlA);\
PyModule_AddIntConstant(m, "CtrlB", CtrlB);\
PyModule_AddIntConstant(m, "CtrlX", CtrlX);\
PyModule_AddIntConstant(m, "CtrlY", CtrlY);\
PyModule_AddIntConstant(m, "CtrlM", CtrlM);

struct Controller {
  PyObject_HEAD
  TXL_Controller *ctrl;
};

static PyMemberDef ControllerMembers[] = {
  {NULL}
};

void ControllerDealloc(Controller*);
PyObject *ControllerNew(PyTypeObject*, PyObject*, PyObject*);
int ControllerInit(Controller*, PyObject*, PyObject*);
PyObject *ControllerUpdate(Controller*, PyObject*);
PyObject *ControllerIsKeyboard(Controller*, PyObject*);
PyObject *ControllerPress(Controller*, PyObject*);
PyObject *ControllerClick(Controller*, PyObject*);
PyObject *ControllerRelease(Controller*, PyObject*);
PyObject *ControllerJoyX(Controller*, PyObject*);
PyObject *ControllerJoyY(Controller*, PyObject*);
PyObject *ControllerMouseX(Controller*, PyObject*);
PyObject *ControllerMouseY(Controller*, PyObject*);
PyObject *ControllerId(Controller*, PyObject*);
PyObject *ControllerRumble(Controller*, PyObject*);

static PyMethodDef ControllerMethods[] = {
  {"update", PyCFunction(ControllerUpdate), METH_NOARGS, "Update the controller's state"},
  {"isKeyboard", PyCFunction(ControllerIsKeyboard), METH_NOARGS, "Check if the controller is a keyboard"},
  {"press", PyCFunction(ControllerPress), METH_VARARGS, "Checks if a button is pressed"},
  {"click", PyCFunction(ControllerClick), METH_VARARGS, "Checks if a button was just pressed"},
  {"release", PyCFunction(ControllerRelease), METH_VARARGS, "Cecks if a button was just released"},
  {"joyX", PyCFunction(ControllerJoyX), METH_NOARGS, "Get the joystick's X position"},
  {"joyY", PyCFunction(ControllerJoyY), METH_NOARGS, "Get the joystick's Y position"},
  {"mouseX", PyCFunction(ControllerMouseX), METH_NOARGS, "Get the mouse's X position"},
  {"mouseY", PyCFunction(ControllerMouseY), METH_NOARGS, "Get the mouse's Y position"},
  {"id", PyCFunction(ControllerId), METH_NOARGS, "Get the id of the controller"},
  {"rumble", PyCFunction(ControllerRumble), METH_VARARGS, "Make the controller vibrate if possible"},
  {NULL}
};

extern PyTypeObject ControllerType;

#endif