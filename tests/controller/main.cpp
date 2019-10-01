#include <cmath>
#include <TEXEL/texel.h>

bool init();
void update();
void render();
void end();

TXL_Display disp;
TXL_Controller *ctrl = nullptr;
bool loop = 1;
TXL_Texture arrow;
float x = 320, y = 180;
float r = 0;

int main(int argc, char **argv) {
  if (init()) {
    while (loop) {
      loop = TXL_Events(&disp);
      
      update();
      render();
    }
    end();
    return 0;
  }
  return 1;
}

bool init() {
  TXL_Init();
  
  if (!disp.init("TEXEL Test")) return 0;
  if (!arrow.load("arrow.png")) return 0;
  ctrl = new TXL_Controller;
  if (!ctrl->init()) {
    delete ctrl;
    ctrl = new TXL_Keyboard;
    ctrl->init();
  }
  return 1;
}

void update() {
  TXL_ManageController(ctrl);

  r = atan2(ctrl->leftJoyY(), ctrl->leftJoyX());
  if (ctrl->buttonClick(CtrlS)) ctrl->rumble(0.85, 250);
  if (ctrl->buttonRelease(CtrlS)) ctrl->rumble(0.25, 250);
  if (ctrl->buttonPress(CtrlS)) {
    x += 4.0f * cos(r);
    y += 4.0f * sin(r);
  }
}

void render() {
  arrow.render(x, y, 2, 2, r * (180.0f / 3.14f));
  disp.refresh();
}

void end() {
  ctrl->end();
  delete ctrl;
  disp.end();
  TXL_End();
}