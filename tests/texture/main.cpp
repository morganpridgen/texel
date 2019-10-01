#include <cmath>
#include <TEXEL/texel.h>

bool init();
void update();
void render();
void end();

TXL_Display disp;
bool loop = 1;
bool pause = 0;
unsigned long t = 0;
TXL_Texture box;
int bX = 320;
int bY = 180;
float bW = 1;
float bH = 1;
float bR = 0;

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
  if (!box.load("box.png", 32, 8)) return 0;
  return 1;
}

void update() {
  t++;
  bR = float(t);
  if (t > 120) {
    bX = 320 + 32 * cos(t * (0.0174) / 2);
    bY = 180 + 32 * sin(t * (0.0174) / 2);
  }
  if (t > 240) {
    bW = 1 + cos(t * (0.0174)) / 2;
    bH = 1 + sin(t * (0.0174)) / 2;
  }
}

void render() {
  box.setClip(((t / 8) % 4) * 8, ((t / 8) % 4) * 8 + 8, 0, 8);
  box.render(bX, bY, bW * 4.0f, bH * 4.0f, bR);
  disp.refresh();
}

void end() {
  disp.end();
  TXL_End();
}