#ifndef texel_solidfillh
#define texel_solidfillh
#include <TEXEL/os.h>

struct TXL_Vert {
  float x;
  float y;
};
struct TXL_Rect {
  float x;
  float y;
  float w;
  float h;
};
struct TXL_Color {
  float r;
  float g;
  float b;
  float a;
};

void TEXELFunc TXL_RenderQuad(const TXL_Vert&, const TXL_Vert&, const TXL_Color&);
void TEXELFunc TXL_RenderQuad(const TXL_Rect&, const TXL_Color&);
inline void TXL_RenderQuad(const float x, const float y, const float w, const float h, const TXL_Color &color) {TXL_RenderQuad({x - w / 2.0f, y - h / 2.0f, w, h}, color);}

#endif