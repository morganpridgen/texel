#include <cmath>
#include <TEXEL/texel.h>

bool init();
void update();
void render();
void end();

TXL_Display disp;
bool loop = 1;

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
  return 1;
}

void update() {
}

void render() {
  TXL_RenderQuad({160, 90, 320, 180}, {1, 1, 1, 1});
  for (int i = 0; i < 16; i++) {
    TXL_RenderLine({320 + 16 * cos((float(i) * 22.5) * (3.14 / 180.0)), 180 + 9 * sin((float(i) * 22.5) * (3.14 / 180.0))}, {320 + 16 * cos((float(i + 1) * 22.5) * (3.14 / 180.0)), 180 + 9 * sin((float(i + 1) * 22.5) * (3.14 / 180.0))}, {float(i) / 16.0, 0, 0, 1});
  }
  disp.refresh();
}

void end() {
  disp.end();
  TXL_End();
}