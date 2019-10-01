#ifndef texelh
#define texelh
#include <TEXEL/display.h>
#include <TEXEL/texture.h>
#include <TEXEL/sound.h>
#include <TEXEL/ctrl.h>
#include <TEXEL/solidfill.h>
#include <TEXEL/file.h>
#include <TEXEL/os.h>
#include <TEXEL/text.h>

bool TEXELFunc TXL_Init();
bool TEXELFunc TXL_Events(TXL_Display*);
void TEXELFunc TXL_End();

void TEXELFunc TXL_Log(char*);

#endif