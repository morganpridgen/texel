#include <cmath>
#include <TEXEL/texel.h>

bool init();
void update();
void render();
void end();

TXL_Display disp;
TXL_Square snd;
int t = 0;
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
  snd = {440, 1.0f, 1.0f, 2};
  TXL_PlaySound(snd);
  snd = {880, 1.0f, 0.5f, 2};
  TXL_PlaySound(snd);
  
  if (!disp.init("TEXEL Test")) return 0;
  return 1;
}

void update() {
}

void render() {
  disp.refresh();
}

void end() {
  disp.end();
  TXL_EndSound();
  TXL_End();
}