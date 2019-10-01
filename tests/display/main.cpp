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
  disp.refresh();
}

void end() {
  disp.end();
  TXL_End();
}