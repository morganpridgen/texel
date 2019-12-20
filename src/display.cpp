#include <TEXEL/display.h>
#include <TEXEL/file.h>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define min(x, y) ((x) < (y) ? (x) : (y))

TXL_Display *gDisp = nullptr;

bool TXL_Display::init(const char name[]) {
  if (gDisp != nullptr) return 0;
  info.rX = TXL_IntResX;
  info.rY = TXL_IntResY;
  info.r = 0.0f;
  info.g = 0.0f;
  info.b = 0.0f;
  info.sR = 1.0f;
  info.fullscreen = 0;
  win = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info.rX, info.rY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (win == nullptr) {
    printf("error creating window (%s)\n", SDL_GetError());
    return 0;
  }
  SDL_Surface *icon = IMG_Load(TXL_DataPath("icon.png"));
  SDL_SetWindowIcon(win, icon);
  SDL_FreeSurface(icon);
  SDL_RaiseWindow(win);
  
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    printf("error creating rendering context (%s)\n", SDL_GetError());
    renderer = SDL_GetRenderer(win);
    if (!renderer) {
      printf("error getting rendering context (%s)\n", SDL_GetError());
      return 0;
    }
  }
  SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
  SDL_RenderSetLogicalSize(renderer, TXL_IntResX, TXL_IntResY);
  SDL_RenderSetViewport(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderClear(renderer);
  
  strcpy(winName, name);
  SDL_RendererInfo rInfo;
  SDL_GetRendererInfo(renderer, &rInfo);
  char dName[64];
  sprintf(dName, "%s (backend: %s)", winName, rInfo.name);
  SDL_SetWindowTitle(win, dName);
  
  gDisp = this;
  lastRender = 0;
  updateMs = 0;
  return 1;
}

void TXL_Display::end() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  gDisp = nullptr;
}

void TXL_Display::refresh() {
  static int refreshes = 0;
  static int lastDelay = 0;
  int cycleTime = lastRender;
  int timeChange = SDL_GetTicks() - lastRender;
  lastRender = SDL_GetTicks();
  updateMs += timeChange;
  if (updateMs > 1000) {
    updateMs %= 1000;
    SDL_RendererInfo rInfo;
    SDL_GetRendererInfo(renderer, &rInfo);
    char dName[64];
    sprintf(dName, "%s (backend: %s, fps: %i)", winName, rInfo.name, refreshes);
    SDL_SetWindowTitle(win, dName);
    refreshes = 0;
  }
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, info.r * 255, info.g * 255, info.b * 255, 255);
  SDL_RenderClear(renderer);
  int delay = int(int((1000 / 60) - (SDL_GetTicks() - cycleTime) + lastDelay) / 2);
  if (delay > 0 && delay < 1000) SDL_Delay(delay);
  lastDelay = delay;
  refreshes++;
};

void TXL_Display::setFill(float nR, float nG, float nB) {
  info.r = nR;
  info.g = nG;
  info.b = nB;
  SDL_SetRenderDrawColor(renderer, info.r * 255, info.g * 255, info.b * 255, 255);
}

void TXL_Display::event(SDL_Event e) {
  SDL_Rect r;
  if (e.type == SDL_WINDOWEVENT && (e.window.event == SDL_WINDOWEVENT_RESIZED)) {
    if (e.window.data1 < TXL_IntResX || e.window.data2 < TXL_IntResY) {
      SDL_SetWindowSize(win, TXL_IntResX, TXL_IntResY);
      info.sR = 1.0f;
      info.rX = TXL_IntResX;
      info.rY = TXL_IntResY;
      r = {0, 0, int(TXL_IntResX), int(TXL_IntResY)};
      SDL_RenderSetViewport(renderer, &r);
      SDL_RenderSetLogicalSize(renderer, TXL_IntResX, TXL_IntResY);
      return;
    }
    SDL_SetWindowSize(win, e.window.data1, e.window.data2);
    info.rX = e.window.data1;
    info.rY = e.window.data2;
    info.sR = min(floor(info.rX / TXL_IntResX), floor(info.rY / TXL_IntResY));
    r = {(info.rX - TXL_IntResX * info.sR) / 2, (info.rY - TXL_IntResY * info.sR) / 2, TXL_IntResX * info.sR, TXL_IntResY * info.sR};
    SDL_RenderSetViewport(renderer, &r);
    SDL_RenderSetLogicalSize(renderer, TXL_IntResX * info.sR, TXL_IntResY * info.sR);
  }
  if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11) {
    info.fullscreen = ~info.fullscreen;
    if (info.fullscreen) {
      SDL_DisplayMode d;
      SDL_GetCurrentDisplayMode(SDL_GetWindowDisplayIndex(win), &d);
      SDL_SetWindowSize(win, d.w, d.h);
      info.rX = d.w;
      info.rY = d.h;
    }
    SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN & info.fullscreen);
    if (!info.fullscreen) {
      SDL_SetWindowSize(win, TXL_IntResX, TXL_IntResY);
      info.rX = TXL_IntResX;
      info.rY = TXL_IntResY;
    }
    info.sR = min(floor(info.rX / TXL_IntResX), floor(info.rY / TXL_IntResY));
    r = {(info.rX - TXL_IntResX * info.sR) / 2, (info.rY - TXL_IntResY * info.sR) / 2, TXL_IntResX * info.sR, TXL_IntResY * info.sR};
    SDL_RenderSetViewport(renderer, &r);
    SDL_RenderSetLogicalSize(renderer, TXL_IntResX * info.sR, TXL_IntResY * info.sR);
  }
}