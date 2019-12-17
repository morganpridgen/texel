#include <TEXEL/solidfill.h>
#include <cmath>
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

void TXL_RenderTri(const TXL_Vert &p1, const TXL_Vert &p2, const TXL_Vert &p3, const TXL_Color &c) {
  SDL_SetRenderDrawColor(gDisp->getRenderer(), c.r * 255, c.g * 255, c.b * 255, c.a * 255);
  
  const TXL_Vert *topP = &p1, *midP = &p2, *botP = &p3, *tmp;
  if (topP->y > midP->y) {
    tmp = topP;
    topP = midP;
    midP = tmp;
  }
  if (midP->y > botP->y) {
    tmp = midP;
    midP = botP;
    botP = tmp;
  }
  if (topP->y > midP->y) {
    tmp = topP;
    topP = midP;
    midP = tmp;
  }
  
  float m1, b1, m2, b2;
  m1 = (botP->y - topP->y) / (botP->x - topP->x);
  b1 = topP->y - m1 * topP->x;
  m2 = (midP->y - topP->y) / (midP->x - topP->x);
  b2 = midP->y - m2 * midP->x;
  for (float i = topP->y; i < midP->y; i += gDisp->pixToCoord(1.0f)) {
    float x1 = i / m1 - b1 / m1, x2 = i / m2 - b2 / m2;
    SDL_Rect r = {gDisp->coordToPix(fmin(x1, x2)), gDisp->coordToPix(i), gDisp->coordToPix(fabs(x2 - x1)), 1};
    SDL_RenderFillRect(gDisp->getRenderer(), &r);
  }
  m2 = (botP->y - midP->y) / (botP->x - midP->x);
  b2 = midP->y - m2 * midP->x;
  for (float i = midP->y; i < botP->y; i += gDisp->pixToCoord(1.0f)) {
    float x1 = i / m1 - b1 / m1, x2 = i / m2 - b2 / m2;
    SDL_Rect r = {gDisp->coordToPix(fmin(x1, x2)), gDisp->coordToPix(i), gDisp->coordToPix(fabs(x2 - x1)), 1};
    SDL_RenderFillRect(gDisp->getRenderer(), &r);
  }
}