#include <cmath>
#include <TEXEL/texel.h>
#include <cmath>

bool init();
void update();
void render();
void end();

TXL_Display disp;
bool loop = 1;
float r = 0;

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
  r++;
}

void render() {
  TXL_RenderQuad({160, 90, 320, 180}, {1, 1, 1, 1});
  for (float i = 0; i < 64.0f; i++) {
    TXL_RenderTri({320.0f, 180.0f}, {320.0f + 80.0f * cos(i * 3.14f / 32.0f), 180.0f + 80.0f * sin(i * 3.14f / 32.0f)}, {320.0f + 80.0f * cos((i + 1) * 3.14f / 32.0f), 180.0f + 80 * sin((i + 1) * 3.14f / 32.0f)}, {fmod(i, 2), 1.0f - fmod(i, 2), fmod(i, 2), 0.5f});
  }
  TXL_RenderTri({320.0f + 80.0f * cos((r + 0) * 3.14f / 180.0f), 180.0f + 80.0f * sin((r + 0) * 3.14f / 180.0f)}, {320.0f + 80.0f * cos((r + 120) * 3.14f / 180.0f), 180.0f + 80.0f * sin((r + 120) * 3.14f / 180.0f)}, {320.0f + 80.0f * cos((r + 240) * 3.14f / 180.0f), 180.0f + 80.0f * sin((r + 240) * 3.14f / 180.0f)}, {1.0f, 0.0f, 0.0f, 0.5f});
  disp.refresh();
}

void end() {
  disp.end();
  TXL_End();
}