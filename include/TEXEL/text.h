#ifndef texel_texth
#define texel_texth

#include <TEXEL/os.h>
#include <TEXEL/texture.h>

bool TEXELFunc TXL_LoadFont(const char*);
void TEXELFunc TXL_UnloadFont();
void TEXELFunc *TXL_RenderText(TXL_Texture*, const char*, float, float, float);

#endif