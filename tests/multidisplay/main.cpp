#include <TEXEL/texel.h>
#define dispCount 3

bool init();
void update();
void render();
void end();

TXL_Display disps[dispCount];
bool loop = 1;

float bX = 320.0f, bY = 180.0f, bDX = 2.0f, bDY = 2.0f;

int main(int argc, char **argv) {
  if (init()) {
    while (loop) {
      loop = TXL_Events(disps, dispCount);
      
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
  
  for (int i = 0; i < dispCount; i++) {
    if (!disps[i].init("TEXEL Test")) return 0;
  }
  return 1;
}

void update() {
  bX += bDX;
  bY += bDY;
  if (bX < 0.0f || bX > 640.0f * dispCount) bDX *= -1;
  if (bY < 0.0f || bY > 360.0f) bDY *= -1;
}

void render() {
  for (int i = 0; i < dispCount; i++) {
    TXL_SetTargetDisplay(&disps[i]);
    TXL_RenderQuad(bX - 640.0f * i, bY, 16, 16, {1.0f, 1.0f, 1.0f, 1.0f});
    disps[i].refresh();
  }
}

void end() {
  for (int i = 0; i < dispCount; i++) disps[i].end();
  TXL_End();
}