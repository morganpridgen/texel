#include <TEXEL/ctrl.h>
#include <cstring>
#include <cstdio>
#include <SDL2/SDL.h>
#include <TEXEL/display.h>

int tCtrls = 0;

bool TXL_Gamepad::init() {
  id = -1;
  ctrl = nullptr;
  b = 0;
  lB = 0;
  aX = 0.0f;
  aY = 0.0f;
  mX = 320.0f;
  mY = 180.0f;
  int ctrlCount = SDL_NumJoysticks();
  int i = 0;
  while (i < ctrlCount) {
    if (!((tCtrls >> i) & 1)) {
      if (SDL_IsGameController(i)) {
        ctrl = SDL_GameControllerOpen(i);
        if (!ctrl) printf("error opening controller %i (%s)\n", i, SDL_GetError());
        else {
          id = i;
          tCtrls |= 1 << i;
          break;
        }
      }
    }
    i++;
  }
  if (id == -1) return 0;
  printf("controller %i connected\n", id);
  return 1;
}

bool TXL_Gamepad::update() {
  lB = b;
  b = 0;
  SDL_GameControllerUpdate();
  if (!SDL_GameControllerGetAttached(ctrl)) {
    printf("controller %i disconnected\n", id);
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
  b |= CtrlM * SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
  if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) aX = -1.0f;
  else if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) aX = 1.0f;
  else aX = float(SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_LEFTX)) / 32768.0f;
  if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_UP)) aY = -1.0f;
  else if (SDL_GameControllerGetButton(ctrl, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) aY = 1.0f;
  else aY = float(SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_LEFTY)) / 32768.0f;
  /*a2X = SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_RIGHTX) / 256;
  a2Y = SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_RIGHTY) / 256;*/
  mX += float(SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_RIGHTX)) / 8192.0f; // 4 px / frame = 240 px / sec
  mY += float(SDL_GameControllerGetAxis(ctrl, SDL_CONTROLLER_AXIS_RIGHTY)) / 8192.0f;
  if (mX < 0.0f) mX = 0.0f;
  if (mX > 640.0f) mX = 640.0f;
  if (mY < 0.0f) mY = 0.0f;
  if (mY > 360.0f) mY = 360.0f;
  return 1;
}

void TXL_Gamepad::end() {
  tCtrls &= ~(1 << id);
  SDL_GameControllerClose(ctrl);
}

void TXL_Gamepad::rumble(float power, int time) {
  if (power < 0.0f) power = 0.0f;
  if (power > 1.0f) power = 1.0f;
  SDL_GameControllerRumble(ctrl, float(0xffff) * power, float(0xffff) * power, time);
}

bool TXL_Keyboard::init() {
  id = 0;
  aX = 0.0f;
  aY = 0.0f;
  mX = 0.0f;
  mY = 0.0f;
  b = 0;
  lB = 0;
  SDL_ShowCursor(SDL_DISABLE);
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
  aX = float(keys[SDL_SCANCODE_D] - keys[SDL_SCANCODE_A]);
  aY = float(keys[SDL_SCANCODE_S] - keys[SDL_SCANCODE_W]);
  int tMX, tMY;
  b |= CtrlM * (SDL_GetMouseState(&tMX, &tMY) & SDL_BUTTON(SDL_BUTTON_LEFT) != 0);
  mX = TXL_GetTargetDisplay()->mouseXToCoord(tMX), mY = TXL_GetTargetDisplay()->mouseYToCoord(tMY);
  if (mX < 0.0f) mX = 0.0f;
  if (mX > 640.0f) mX = 640.0f;
  if (mY < 0.0f) mY = 0.0f;
  if (mY > 360.0f) mY = 360.0f;
  return 1;
}

void TXL_Keyboard::end() {
  SDL_ShowCursor(SDL_ENABLE);
}

void TXL_ManageController(TXL_Controller *&ctrl) {
  TXL_Controller *oldCtrl = nullptr;
  if (!ctrl) {
    ctrl = new TXL_Gamepad;
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
      ctrl = new TXL_Gamepad;
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