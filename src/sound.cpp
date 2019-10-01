#include <TEXEL/sound.h>
#include <TEXEL/file.h>
#include <SDL2/SDL.h>
#include <cstring>
#include <cmath>
#define tmod(x, y) (x - y * floor(x / y))
#define channelCount 4
#define logSound 0

void TXL_HandleAudio(void *, unsigned char*, int);
SDL_AudioDeviceID TXL_SoundDev;
TXL_Square *squares[channelCount];
TXL_Noise *noises[channelCount];
TXL_Triangle *triangles[channelCount];
TXL_Sawtooth *saws[channelCount];
float freq;
#if logSound != 0
  TXL_File recording;
#endif

bool TXL_InitSound() {
  SDL_AudioSpec want, have;
  memset(&want, 0, sizeof(want));
  want.freq = 48000;
  want.format = AUDIO_U8;
  want.channels = 1;
  want.samples = 4096;
  want.callback = TXL_HandleAudio;
  TXL_SoundDev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
  if (TXL_SoundDev == 0) {
    printf("Error setting up sound. (%s)\n", SDL_GetError());
    return 0;
  }
  freq = have.freq;
  if (TXL_SoundDev == 0) return 0;
  for (int i = 0; i < channelCount; i++) {
    squares[i] = nullptr;
    noises[i] = nullptr;
    triangles[i] = nullptr;
    saws[i] = nullptr;
  }
  #if logSound != 0
    recording.init("recording.bin", "wb");
  #endif
  SDL_PauseAudioDevice(TXL_SoundDev, 0);
  return 1;
}

void TXL_PlaySound(const TXL_Square &newSound) {
  float maxVol = 0;
  int highChan = 0;
  for (int i = 0; i < channelCount; i++) {
    if (!squares[i]) {
      highChan = i;
      break;
    }
    if (squares[i]->vol > maxVol) {
      maxVol = squares[i]->vol;
      highChan = i;
    }
  }
  if (!squares[highChan]) squares[highChan] = new TXL_Square;
  *squares[highChan] = newSound;
}

void TXL_PlaySound(const TXL_Noise &newSound) {
  float maxVol = 0;
  int highChan = 0;
  for (int i = 0; i < channelCount; i++) {
    if (!noises[i]) {
      highChan = i;
      break;
    }
    if (noises[i]->vol > maxVol) {
      maxVol = noises[i]->vol;
      highChan = i;
    }
  }
  if (!noises[highChan]) noises[highChan] = new TXL_Noise;
  *noises[highChan] = newSound;
}

void TXL_PlaySound(const TXL_Triangle &newSound) {
  float maxVol = 0;
  int highChan = 0;
  for (int i = 0; i < channelCount; i++) {
    if (!triangles[i]) {
      highChan = i;
      break;
    }
    if (triangles[i]->vol > maxVol) {
      maxVol = triangles[i]->vol;
      highChan = i;
    }
  }
  if (!triangles[highChan]) triangles[highChan] = new TXL_Triangle;
  *triangles[highChan] = newSound;
}

void TXL_PlaySound(const TXL_Sawtooth &newSound) {
  float maxVol = 0;
  int highChan = 0;
  for (int i = 0; i < channelCount; i++) {
    if (!saws[i]) {
      highChan = i;
      break;
    }
    if (saws[i]->vol > maxVol) {
      maxVol = saws[i]->vol;
      highChan = i;
    }
  }
  if (!saws[highChan]) saws[highChan] = new TXL_Sawtooth;
  *saws[highChan] = newSound;
}

void TXL_EndSound() {
  #if logSound != 0
    recording.close();
  #endif
  SDL_CloseAudioDevice(TXL_SoundDev);
}

void TXL_HandleAudio(void *userdata, unsigned char *stream, int len) {
  static float t = 0;
  int tSounds, sqSnd, nsSnd, trSnd, swSnd, bitShift;
  for (int i = 0; i < len; i++) {
    tSounds = 0;
    sqSnd = 0, nsSnd = 0, trSnd = 0, swSnd = 0;
    for (int j = 0; j < channelCount; j++) {
      if (squares[j]) {
        tSounds++;
        sqSnd += (unsigned char)(float(int(t * squares[j]->freq * 2.0f) % 8 < (squares[j]->duty == 0 ? 1 : (squares[j]->duty == 1 ? 2 : (squares[j]->duty == 2 ? 4 : 6)))) * 255.0f * squares[j]->vol);
        squares[j]->vol -= squares[j]->fade / freq;
        if (squares[j]->vol <= 0.0f) {
          delete squares[j];
          squares[j] = nullptr;
        }
      }
      if (noises[j]) {
        tSounds++;
        nsSnd += (unsigned char)(float(noises[j]->seed & 0b11111111) * noises[j]->vol);
        bitShift = noises[j]->bit ? 15 : 31;
        if (i % noises[j]->cycle == 0) {
          if (noises[j]->seed == 0) noises[j]->seed = ~noises[j]->seed;
          noises[j]->seed = (noises[j]->seed << 1) | ((noises[j]->seed >> bitShift & 0b1) ^ (noises[j]->seed >> (bitShift - 1) & 0b1));
        }
        noises[j]->vol -= noises[j]->fade / freq;
        if (noises[j]->vol <= 0.0f) {
          delete noises[j];
          noises[j] = nullptr;
        }
      }
      if (triangles[j]) {
        tSounds++;
        if (tmod(t * triangles[j]->freq * 2.0f, 2) < 1) trSnd += (unsigned char)(tmod(t * triangles[j]->freq * 2.0f, 2) * 255.0f * triangles[j]->vol);
        else trSnd += (unsigned char)(tmod(t * triangles[j]->freq * -2.0f, 2) * 255.0f * triangles[j]->vol);
        triangles[j]->vol -= triangles[j]->fade / freq;
        if (triangles[j]->vol <= 0.0f) {
          delete triangles[j];
          triangles[j] = nullptr;
        }
      }
      if (saws[j]) {
        tSounds++;
        swSnd += (unsigned char)(tmod(t * saws[j]->freq, 1) * 255.0f * saws[j]->vol);
        saws[j]->vol -= saws[j]->fade / freq;
        if (saws[j]->vol <= 0.0f) {
          delete saws[j];
          saws[j] = nullptr;
        }
      }
    }
    stream[i] = tSounds == 0 ? 0 : (sqSnd + nsSnd + trSnd + swSnd) / tSounds;
    t += 1.0f / freq;
    if (t >= 1.0f) t -= 1.0f;
  }
  #if logSound != 0
    recording.write(stream, len);
  #endif
}