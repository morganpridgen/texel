#include <cmath>
#include <TEXEL/texel.h>

bool init();
void update();
void render();
void end();

TXL_Display disp;
TXL_Controller *ctrl = nullptr;
TXL_File file;
bool loop = 1;
TXL_Texture arrow;
float r = 0;
bool recording = 1;
int t = 600;

int main(int argc, char **argv) {
  if (init()) {
    while (loop) {
      loop = TXL_Events(&disp);
      
      update();
      render();
    }
    end();
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
  
  if (t >= 600) {
    recording = !recording;
    printf(recording ? "Recording...\n" : "Playback...\n");
    //file.init("angles.bin", recording ? "wb" : "rb");
    file.close();
    if (recording) file.init("angles.bin", "wb");
    else file.init("angles.bin", "rb");
    t = 0;
  }

  if (recording == 1) {
    r = atan2(ctrl->leftJoyY(), ctrl->leftJoyX());
    file.write(&r);
  } else if (recording == 0) file.read(&r);
  t++;
}

void render() {
  arrow.render(320, 180, 2, 2, r * (180.0f / 3.14f));
  TXL_RenderQuad({0, 0}, {640.0f * (float(t) / 600.0f), 16.0f}, {1, 1, 1, 1});
  disp.refresh();
}

void end() {
  file.close();
  ctrl->end();
  delete ctrl;
  disp.end();
  TXL_End();
}