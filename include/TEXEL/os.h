#ifndef texel_osh
#define texel_osh

#if defined(__linux__)
  #define OS 0
  #define TEXELFunc
#elif defined(_WIN32)
  #define OS 1
  #ifdef TEXELDLL
    #define TEXELFunc __declspec(dllexport)
  #else
    #define TEXELFunc __declspec(dllimport)
  #endif
#else
  #error TEXEL does not support this operating system.
#endif
#define linux 0
#define windows 1

inline int TXL_GetOS() {return OS;}

#endif