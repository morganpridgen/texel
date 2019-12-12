#include <TEXEL/text.h>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <TEXEL/texture.h>
#include <TEXEL/file.h>

SDL_Surface *TXL_Font = nullptr;

bool TXL_LoadFont(const char *path) {
  TXL_Font = IMG_Load(path);
  if (!TXL_Font) {
    printf("error loading font (%s)\n", IMG_GetError());
    return 0;
  }
  SDL_ConvertSurfaceFormat(TXL_Font, SDL_PIXELFORMAT_RGBA32, 0);
  return 1;
}

void TXL_UnloadFont() {
  SDL_FreeSurface(TXL_Font);
}

SDL_Surface *surfaceText(const char *text, int r, int g, int b) {
  SDL_SetSurfaceColorMod(TXL_Font, r, g, b);
  int chrS = TXL_Font->h;
  SDL_Surface *out = SDL_CreateRGBSurfaceWithFormat(0, chrS * strlen(text), chrS, 32, SDL_PIXELFORMAT_RGBA32);
  if (!out) {
    printf("error creating text surface (%s)\n", IMG_GetError());
    return nullptr;
  }
  int i = 0;
  while (true) {
    if (text[i] == 0) break;
    SDL_Rect clip = {(text[i] - 32) * chrS, 0, chrS, chrS};
    SDL_Rect rect = {i * chrS, 0, chrS, chrS};
    SDL_BlitSurface(TXL_Font, &clip, out, &rect);
    i++;
  }
  return out;
}

void *TXL_RenderText(TXL_Texture *tex, const char *text, float r, float g, float b) {
  SDL_Surface *out = surfaceText(text, r * 255, g * 255, b * 255);
  if (!tex->load(out, 16 * strlen(text), 16)) return nullptr;
  return tex;
}