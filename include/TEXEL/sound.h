#ifndef texel_soundh
#define texel_soundh
#include <TEXEL/os.h>

struct TXL_Square {
  float freq, vol, fade;
  int duty;
};
struct TXL_Noise {
  float vol, fade;
  int seed, cycle;
  bool bit;
};
struct TXL_Triangle {
  float freq, vol, fade;
};
struct TXL_Sawtooth {
  float freq, vol, fade;
};

bool TEXELFunc TXL_InitSound();

void TEXELFunc TXL_PlaySound(const TXL_Square&);
void TEXELFunc TXL_PlaySound(const TXL_Noise&);
void TEXELFunc TXL_PlaySound(const TXL_Triangle&);
void TEXELFunc TXL_PlaySound(const TXL_Sawtooth&);

void TEXELFunc TXL_SetMChannel(const TXL_Square&, int);
void TEXELFunc TXL_SetMChannel(const TXL_Noise&, int);
void TEXELFunc TXL_SetMChannel(const TXL_Triangle&, int);
void TEXELFunc TXL_SetMChannel(const TXL_Sawtooth&, int);

void TEXELFunc TXL_ClearSounds();

void TEXELFunc TXL_EndSound();

#endif