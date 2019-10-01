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
TXL_Texture *text;
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
  if (!TXL_LoadFont("font.png")) return 0;
  text = TXL_RenderText("Hello! :)", 0.9f, 1.0f, 1.0f);
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
  text->render(bX, bY, bW, bH, bR);
  disp.refresh();
}

void end() {
  text->free();
  delete text;
  TXL_UnloadFont();
  disp.end();
  TXL_End();
}