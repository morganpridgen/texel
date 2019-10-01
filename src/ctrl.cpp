#include <TEXEL/ctrl.h>
#include <cstring>
#include <cstdio>
#include <SDL2/SDL.h>

int tCtrls = 0;

bool TXL_Controller::init() {
  id = -1;
  ctrl = nullptr;
  b = 0;
  lB = 0;
  aX = 0;
  aY = 0;
  a2X = 0;
  a2Y = 0;
  int ctrlCount = SDL_NumJoysticks();
  int i = 0;
  while (i < ctrlCount) {
    if (!((tCtrls >> i) & 1)) {
      if (SDL_IsGameController(i)) {
        ctrl = SDL_GameControllerOpen(i);
        if (!ctrl) printf("Error opening controller %i. %s\n", i, SDL_GetError());
        else {
          id = i;
          tCtrls |= 1 << i;
          break;
        }
      }
    }
    i++;
  }
  if (id == -1) {
    return 0;
  }
  printf("Controller %i connected\n", id);
  return 1;
}

bool TXL_Controller::update() {
  lB = b;
  b = 0;
  SDL_GameControllerUpdate();
  if (!SDL_GameControllerGetAttached(ctrl)) {
    printf("Controller %i disconnected.\n", id);
    return 0;
  }
  b |= CtrlN * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_Y);
  b |= CtrlS * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_A);
  b |= CtrlE * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_B);
  b |= CtrlW * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_X);
  b |= CtrlStart * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_START);
  b |= CtrlSelect * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_BACK);
  b |= CtrlL * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  b |= CtrlR * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
  if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) aX = -127;
  else if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) aX = 127;
  else aX = SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_LEFTX) / 256;
  if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_UP)) aY = -127;
  else if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) aY = 127;
  else aY = SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_LEFTY) / 256;
  a2X = SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_RIGHTX) / 256;
  a2Y = SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_RIGHTY) / 256;
  return 1;
}

void TXL_Controller::end() {
  tCtrls &= ~(1 << id);
  SDL_GameControllerClose(ctrl);
}

void TXL_Controller::rumble(float power, int time) {
  if (power < 0.0f) power = 0.0f;
  if (power > 1.0f) power = 1.0f;
  SDL_GameControllerRumble(ctrl, float(0xffff) * power, float(0xffff) * power, time);
}

bool TXL_Keyboard::init() {
  id = 0;
  aX = 0;
  aY = 0;
  a2X = 0;
  a2Y = 0;
  b = 0;
  lB = 0;
  ctrl = nullptr;
  return 1;
};

bool getKey(SDL_Keycode key) {
  return SDL_GetKeyboardState(NULL)[key];
}

bool TXL_Keyboard::update() {
  lB = b;
  b = 0;
  const unsigned char *keys = SDL_GetKeyboardState(NULL);
  b |= CtrlS * (keys[SDL_SCANCODE_SPACE]);
  b |= CtrlW * (keys[SDL_SCANCODE_LSHIFT]);
  b |= CtrlE * (keys[SDL_SCANCODE_K]);
  b |= CtrlN * (keys[SDL_SCANCODE_L]);
  b |= CtrlStart * (keys[SDL_SCANCODE_RETURN]);
  b |= CtrlSelect * (keys[SDL_SCANCODE_TAB]);
  b |= CtrlL * (keys[SDL_SCANCODE_J]);
  b |= CtrlR * (keys[SDL_SCANCODE_SEMICOLON]);
  aX = 127 * (keys[SDL_SCANCODE_D] - keys[SDL_SCANCODE_A]);
  aY = 127 * (keys[SDL_SCANCODE_S] - keys[SDL_SCANCODE_W]);
  return 1;
}

void TXL_Keyboard::end() {
}

void TXL_ManageController(TXL_Controller *&ctrl) {
  TXL_Controller *oldCtrl = nullptr;
  if (!ctrl) {
    ctrl = new TXL_Controller;
    if (!ctrl->init()) {
      delete ctrl;
      ctrl = nullptr;
      return;
    }
  }
  if (ctrl->getId() == 0) {
    if (ctrl->isKeyboard()) {
      ctrl->update();
      oldCtrl = ctrl;
      ctrl = new TXL_Controller;
      if (ctrl->init()) {
        oldCtrl->end();
        delete oldCtrl;
        ctrl->update();
      } else {
        delete ctrl;
        ctrl = oldCtrl;
      }
    } else if (!ctrl->update()) {
      ctrl->end();
      delete ctrl;
      ctrl = new TXL_Keyboard;
      ctrl->init();
    }
  } else if (!ctrl->update()) {
    ctrl->end();
    delete ctrl;
    ctrl = nullptr;
  }
}