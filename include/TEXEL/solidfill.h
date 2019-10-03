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

#endif