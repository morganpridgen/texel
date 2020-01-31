#include <TEXEL/solidfill.h>
#include <cmath>
#include <TEXEL/display.h>
#include <SDL2/SDL.h>

void TXL_RenderQuad(const TXL_Vert &v1, const TXL_Vert &v2, const TXL_Color &c) {
  SDL_SetRenderDrawColor(TXL_GetTargetDisplay()->getRenderer(), c.r * 255, c.g * 255, c.b * 255, c.a * 255);
  SDL_Rect r = {TXL_GetTargetDisplay()->coordToPix(v1.x), TXL_GetTargetDisplay()->coordToPix(v1.y), TXL_GetTargetDisplay()->coordToPix(v2.x - v1.x), TXL_GetTargetDisplay()->coordToPix(v2.y - v1.y)};
  if (r.w < 0 || r.h < 0) return;
  SDL_RenderFillRect(TXL_GetTargetDisplay()->getRenderer(), &r);
}

void TXL_RenderQuad(const TXL_Rect &b, const TXL_Color &c) {
  SDL_SetRenderDrawColor(TXL_GetTargetDisplay()->getRenderer(), c.r * 255, c.g * 255, c.b * 255, c.a * 255);
  SDL_Rect r = {TXL_GetTargetDisplay()->coordToPix(b.x), TXL_GetTargetDisplay()->coordToPix(b.y), TXL_GetTargetDisplay()->coordToPix(b.w), TXL_GetTargetDisplay()->coordToPix(b.h)};
  if (r.w < 0 || r.h < 0) return;
  SDL_RenderFillRect(TXL_GetTargetDisplay()->getRenderer(), &r);
}

void TXL_RenderTri(const TXL_Vert &p1, const TXL_Vert &p2, const TXL_Vert &p3, const TXL_Color &c) {
  SDL_SetRenderDrawColor(TXL_GetTargetDisplay()->getRenderer(), c.r * 255, c.g * 255, c.b * 255, c.a * 255);
  
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
  for (float i = topP->y; i < midP->y; i += TXL_GetTargetDisplay()->pixToCoord(1.0f)) {
    float x1 = i / m1 - b1 / m1, x2 = i / m2 - b2 / m2;
    if (topP->x == botP->x) x1 = topP->x;
    if (topP->x == midP->x) x2 = midP->x;
    SDL_Rect r = {TXL_GetTargetDisplay()->coordToPix(fmin(x1, x2)), TXL_GetTargetDisplay()->coordToPix(i), TXL_GetTargetDisplay()->coordToPix(fabs(x2 - x1)), 1};
    SDL_RenderFillRect(TXL_GetTargetDisplay()->getRenderer(), &r);
  }
  m2 = (botP->y - midP->y) / (botP->x - midP->x);
  b2 = midP->y - m2 * midP->x;
  for (float i = midP->y; i < botP->y; i += TXL_GetTargetDisplay()->pixToCoord(1.0f)) {
    float x1 = i / m1 - b1 / m1, x2 = i / m2 - b2 / m2;
    if (topP->x == botP->x) x1 = topP->x;
    if (midP->x == botP->x) x2 = midP->x;
    SDL_Rect r = {TXL_GetTargetDisplay()->coordToPix(fmin(x1, x2)), TXL_GetTargetDisplay()->coordToPix(i), TXL_GetTargetDisplay()->coordToPix(fabs(x2 - x1)), 1};
    SDL_RenderFillRect(TXL_GetTargetDisplay()->getRenderer(), &r);
  }
}