#ifndef texel_displayh
#define texel_displayh

#include <SDL2/SDL.h>
#include <TEXEL/os.h>

#define TXL_IntResX 640.0f
#define TXL_IntResY 360.0f

struct TXL_DisplayInfo { // misc info about display
  int rX;
  int rY;
  float r, g, b;
  char fullscreen;
  float sR;
};

class TEXELFunc TXL_Display { // display handler
  private:
    TXL_DisplayInfo info;
    SDL_Window *win;
    SDL_Renderer *renderer;
    unsigned int lastRender;
  public:
    bool init(const char[]);
    void end();
    void refresh();
    void setFill(float, float, float);
    void event(SDL_Event);
    SDL_Renderer *getRenderer() {return renderer;}
    int coordToPix(float coord) {return round(coord * info.sR);}
    
};

extern TEXELFunc TXL_Display *gDisp;

#endif