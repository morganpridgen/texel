#ifndef texel_texth
#define texel_texth

#include <TEXEL/os.h>
#include <TEXEL/texture.h>

bool TEXELFunc TXL_LoadFont(const char*);
void TEXELFunc TXL_UnloadFont();
TXL_Texture TEXELFunc *TXL_RenderText(const char*, float, float, float);

#endif