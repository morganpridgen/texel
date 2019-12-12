#include <TEXEL/texel.h>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool TXL_Init() {
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  printf("TEXEL compiled with SDL %i.%i.%i\n      linking  with SDL %i.%i.%i\n", compiled.major, compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);\
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL did not start (%s)\n", SDL_GetError());
    return 0;
  }
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_Image did not start (%s)\n", IMG_GetError());
    return 0;
  }
  
  TXL_InitSound();
  TXL_InitEndian();
  TXL_InitSocket();
  return 1;
}

bool TXL_Events(TXL_Display *disp) {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) return 0;
    disp->event(e);
  }
  return 1;
}

void TXL_End() {
  TXL_EndSound();
  TXL_EndSocket();
  SDL_Quit();
}