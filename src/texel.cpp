#include <TEXEL/texel.h>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool TXL_Init() {
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  printf("Texel compiled with SDL %d.%d.%d. Linking with SDL %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch, linked.major, linked.minor, linked.patch);
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    printf("SDL did not start. %s\n", SDL_GetError());
    return 0;
  }
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_Image did not start. %s\n", IMG_GetError());
    return 0;
  }
  
  TXL_InitSound();
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
  SDL_Quit();
}

void TXL_Log(char *txt) {
  printf(txt);
  FILE * f = fopen("log.txt", "a");
  fprintf(f, txt);
  fclose(f);
}