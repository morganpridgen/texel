#include <TEXEL/solidfill.h>
#include <TEXEL/display.h>
#include <SDL2/SDL.h>

void TXL_RenderQuad(const TXL_Vert &v1, const TXL_Vert &v2, const TXL_Color &c) {
  SDL_SetRenderDrawColor(gDisp->getRenderer(), c.r * 255, c.g * 255, c.b * 255, c.a * 255);
  SDL_Rect r = {gDisp->coordToPix(v1.x), gDisp->coordToPix(v1.y), gDisp->coordToPix(v2.x - v1.x), gDisp->coordToPix(v2.y - v1.y)};
  if (r.w < 0 || r.h < 0) return;
  SDL_RenderFillRect(gDisp->getRenderer(), &r);
}

void TXL_RenderQuad(const TXL_Rect &b, const TXL_Color &c) {
  SDL_SetRenderDrawColor(gDisp->getRenderer(), c.r * 255, c.g * 255, c.b * 255, c.a * 255);
  SDL_Rect r = {gDisp->coordToPix(b.x), gDisp->coordToPix(b.y), gDisp->coordToPix(b.w), gDisp->coordToPix(b.h)};
  if (r.w < 0 || r.h < 0) return;
  SDL_RenderFillRect(gDisp->getRenderer(), &r);
}