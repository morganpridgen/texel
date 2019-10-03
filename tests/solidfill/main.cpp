#include <cmath>
#include <TEXEL/texel.h>
#include <cmath>

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
  for (float i = 0; i < 16.0f; i ++) TXL_RenderQuad(320, 180, 128.0f * cos(i * 3.14f / 32.0f), 128.0f * sin(i * 3.14f / 32.0f), {fmod(i, 2), 1.0f - fmod(i, 2), fmod(i, 2), 1});
  disp.refresh();
}

void end() {
  disp.end();
  TXL_End();
}