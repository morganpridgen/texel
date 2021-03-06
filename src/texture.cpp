#include <TEXEL/texture.h>
#include <TEXEL/display.h>
#include <cstdio>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

TXL_Texture::TXL_Texture() {
  texture = nullptr;
  tW = 0;
  tH = 0;
  iW = 0;
  iH = 0;
  cL = 0.0f;
  cR = 1.0f;
  cT = 0.0f;
  cB = 1.0f;
}

bool TXL_Texture::load(SDL_Surface *surf, int w, int h) {
  tW = surf->w;
  tH = surf->h;
  if (w == -1 || h == -1) {
    iW = tW;
    iH = tH;
  } else {
    iW = w;
    iH = h;
  }
  
  texture = SDL_CreateTextureFromSurface(TXL_GetTargetDisplay()->getRenderer(), surf);
  if (!texture) {
    printf("error creating texture.\n");
    return 0;
  }
  SDL_FreeSurface(surf);
  return 1;
}

bool TXL_Texture::load(const char path[], int w, int h) {
  free();
  SDL_Surface *surf = IMG_Load(path);
  if (!surf) {
    printf("error loading texture %s (%s)\n", path, IMG_GetError());
    return 0;
  }
  return load(surf, w, h);
}

void TXL_Texture::free() {
  if (texture) SDL_DestroyTexture(texture);
  texture = nullptr;
}

void TXL_Texture::render(float x, float y, float sX, float sY, float r) {
  SDL_Rect sR, dR;
  sR = {round(fmin(cL, cR) * tW), round(fmin(cT, cB) * tH), round(fabs(cR - cL) * tW), round(fabs(cB - cT) * tH)};
  float w = iW * sX * fabs(cR - cL), h = iH * sY * fabs(cB - cT);
  dR = {TXL_GetTargetDisplay()->coordToPix(x - (w / 2.0f)), TXL_GetTargetDisplay()->coordToPix(y - (h / 2.0f)), TXL_GetTargetDisplay()->coordToPix(w), TXL_GetTargetDisplay()->coordToPix(h)};
  int flip;
  if (cL > cR) flip = flip | SDL_FLIP_HORIZONTAL;
  if (cT > cB) flip = flip | SDL_FLIP_VERTICAL;
  SDL_RenderCopyEx(TXL_GetTargetDisplay()->getRenderer(), texture, &sR, &dR, r, NULL, (SDL_RendererFlip)flip);
}

void TXL_Texture::render(float x, float y, float sX, float sY) {
  if (cL > cR || cT > cB) {
    render(x, y, sX, sY, 0);
    return;
  }
  SDL_Rect sR, dR;
  sR = {round(cL * tW), round(cT * tH), round((cR - cL) * tW), round((cB - cT) * tH)};
  float w = iW * sX * (cR - cL), h = iH * sY * (cB - cT);
  dR = {TXL_GetTargetDisplay()->coordToPix(x - (w / 2.0f)), TXL_GetTargetDisplay()->coordToPix(y - (h / 2.0f)), TXL_GetTargetDisplay()->coordToPix(w), TXL_GetTargetDisplay()->coordToPix(h)};
  SDL_RenderCopy(TXL_GetTargetDisplay()->getRenderer(), texture, &sR, &dR);
}

void TXL_Texture::setClip(float nL, float nR, float nT, float nB) {
  cL = nL / iW;
  cR = nR / iW;
  cT = nT / iH;
  cB = nB / iH;
}

void TXL_Texture::setColorMod(float r, float g, float b) {
  SDL_SetTextureColorMod(texture, r * 255, g * 255, b * 255);
}

void TXL_Texture::setColorMod(float a) {
  SDL_SetTextureAlphaMod(texture, a * 255);
}