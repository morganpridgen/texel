#include <TEXEL/sound.h>
#include <TEXEL/file.h>
#include <SDL2/SDL.h>
#include <cstring>
#include <cmath>
#define tmod(x, y) (x - y * floor(x / y))
#define sChannelCount 2
#define mChannelCount 2
#define channelCount (sChannelCount + mChannelCount)
#define logSound 0

void TXL_HandleAudio(void *, float*, int);
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
  want.format = AUDIO_F32SYS;
  want.channels = 1;
  want.samples = 4096;
  want.callback = (SDL_AudioCallback)TXL_HandleAudio;
  TXL_SoundDev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
  if (TXL_SoundDev == 0) {
    printf("error setting up sound (%s)\n", SDL_GetError());
    return 0;
  }
  freq = have.freq;
  for (int i = 0; i < channelCount; i++) {
    squares[i] = nullptr;
    noises[i] = nullptr;
    triangles[i] = nullptr;
    saws[i] = nullptr;
  }
  #if logSound != 0
    recording.init("recording.bin", 'w');
  #endif
  SDL_PauseAudioDevice(TXL_SoundDev, 0);
  return 1;
}

void TXL_PlaySound(const TXL_Square &newSound) {
  float maxVol = 0;
  int highChan = 0;
  for (int i = mChannelCount; i < channelCount; i++) {
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
  for (int i = mChannelCount; i < channelCount; i++) {
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
  for (int i = mChannelCount; i < channelCount; i++) {
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
  for (int i = mChannelCount; i < channelCount; i++) {
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

void TXL_SetMChannel(const TXL_Square &newSound, int chan) {
  if (chan < 0 || chan >= mChannelCount) return;
  if (!squares[chan]) squares[chan] = new TXL_Square;
  *squares[chan] = newSound;
}

void TXL_SetMChannel(const TXL_Noise &newSound, int chan) {
  if (chan < 0 || chan >= mChannelCount) return;
  if (!noises[chan]) noises[chan] = new TXL_Noise;
  *noises[chan] = newSound;
}

void TXL_SetMChannel(const TXL_Triangle &newSound, int chan) {
  if (chan < 0 || chan >= mChannelCount) return;
  if (!triangles[chan]) triangles[chan] = new TXL_Triangle;
  *triangles[chan] = newSound;
}

void TXL_SetMChannel(const TXL_Sawtooth &newSound, int chan) {
  if (chan < 0 || chan >= mChannelCount) return;
  if (!saws[chan]) saws[chan] = new TXL_Sawtooth;
  *saws[chan] = newSound;
}

void TXL_ClearSounds() {
  for (int i = 0; i < channelCount; i++) {
    if (squares[i]) {
      delete squares[i];
      squares[i] = nullptr;
    }
    if (noises[i]) {
      delete noises[i];
      noises[i] = nullptr;
    }
    if (triangles[i]) {
      delete triangles[i];
      triangles[i] = nullptr;
    }
    if (saws[i]) {
      delete saws[i];
      saws[i] = nullptr;
    }
  }
}

void TXL_EndSound() {
  TXL_ClearSounds();
  #if logSound != 0
    recording.close();
  #endif
  SDL_CloseAudioDevice(TXL_SoundDev);
}

void TXL_HandleAudio(void *userdata, float *stream, int len) {
  static float t = 0;
  int tSounds, bitShift;
  float sqSnd, nsSnd, trSnd, swSnd;
  for (int i = 0; i < len / sizeof(float); i++) {
    sqSnd = 0, nsSnd = 0, trSnd = 0, swSnd = 0;
    for (int j = 0; j < channelCount; j++) {
      if (squares[j]) {
        sqSnd += (float(int(t * squares[j]->freq * 2.0f) % 8 < (squares[j]->duty == 0 ? 1 : (squares[j]->duty == 1 ? 2 : (squares[j]->duty == 2 ? 4 : 6)))) - 0.5f) * squares[j]->vol;
        squares[j]->vol -= squares[j]->fade / freq;
        if (squares[j]->vol <= 0.0f) {
          delete squares[j];
          squares[j] = nullptr;
        }
      }
      if (noises[j]) {
        nsSnd += float(noises[j]->seed & 0b11111111) / 255.0f * noises[j]->vol;
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
        if (tmod(t * triangles[j]->freq * 2.0f, 2) < 1) trSnd += (tmod(t * triangles[j]->freq * 2.0f, 2) - 0.5f) * triangles[j]->vol;
        else trSnd += (tmod(t * triangles[j]->freq * -2.0f, 2) - 0.5f) * triangles[j]->vol;
        triangles[j]->vol -= triangles[j]->fade / freq;
        if (triangles[j]->vol <= 0.0f) {
          delete triangles[j];
          triangles[j] = nullptr;
        }
      }
      if (saws[j]) {
        swSnd += (tmod(t * saws[j]->freq, 1) - 0.5f) * saws[j]->vol;
        saws[j]->vol -= saws[j]->fade / freq;
        if (saws[j]->vol <= 0.0f) {
          delete saws[j];
          saws[j] = nullptr;
        }
      }
    }
    stream[i] = (sqSnd + nsSnd + trSnd + swSnd) / (4 * channelCount);
    t += 1.0f / freq;
    if (t >= 1.0f) t -= 1.0f;
  }
  #if logSound != 0
    recording.write(stream, len);
  #endif
}