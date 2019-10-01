#include <TEXEL/file.h>
#include <TEXEL/os.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if OS == linux
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/stat.h>
#endif
#if OS == windows
  #include <windows.h>
#endif

char baseDir[128];
char savePath[128];
char dataPath[128];

void TXL_InitPaths(const char *saveName) {
  char tmpPath[128];
  int i = 0;
  #if OS == linux
    tmpPath[readlink("/proc/self/exe", tmpPath, 128)] = 0;
    realpath(tmpPath, baseDir);
  #elif OS == windows
    tmpPath[GetModuleFileName(NULL, tmpPath, 128)] = 0;
    GetFullPathName(tmpPath, 128, baseDir, NULL);
  #endif
  i = 0;
  while (1) {
    if (baseDir[i] == 0) break;
    i++;
  }
  i--;
  baseDir[i] = 0;
  while (1) {
    i--;
    if (baseDir[i] == '/' || baseDir[i] == '\\') {
      baseDir[i] = 0;
      break;
    }
    baseDir[i] = 0;
  }
  sprintf(dataPath, "%s/res", baseDir);
  memset(tmpPath, 0, 128);
  #if OS == linux
    char *xdgPath = getenv("XDG_DATA_HOME");
    if (xdgPath && strlen(xdgPath) > 0) {
      i = 0;
      while (1) {
        tmpPath[i] = xdgPath[i];
        i++;
        if (xdgPath[i] == ':' || xdgPath[i] == 0) {
          tmpPath[i] = 0;
          break;
        }
      }
    } else sprintf(tmpPath, "%s/.local/share", getenv("HOME"));
  #elif OS == windows
    strcpy(tmpPath, getenv("APPDATA"));
  #endif
  sprintf(savePath, "%s/%s", tmpPath, saveName);
  printf("Saving data to %s\n", savePath);
  #if OS == linux
    struct stat info;
    if (stat(savePath, &info) == 0 && info.st_mode & S_IFDIR) return;
    mkdir(savePath, 0700);
  #elif OS == windows
    DWORD stat = GetFileAttributes(savePath);
    if (stat == INVALID_FILE_ATTRIBUTES && GetLastError() != ERROR_FILE_NOT_FOUND && stat & FILE_ATTRIBUTE_DIRECTORY) return;
    CreateDirectory(savePath, NULL);
  #endif
}

char *TXL_DataPath(const char *file) {
  static char out[64];
  memset(out, 0, 64);
  sprintf(out, "%s/%s", dataPath, file);
  return out;
}

char *TXL_SavePath(const char *file) {
  static char out[64];
  memset(out, 0, 64);
  sprintf(out, "%s/%s", savePath, file);
  return out;
}

bool TXL_File::init(const char *path, const char *mode) {
  close();
  char *newMode = new char[strlen(mode) + 2];
  sprintf(newMode, "%sb", mode);
  file = fopen(path, newMode);
  delete [] newMode;
  return file != NULL;
}

bool TXL_File::read(void *data, const int len) {
  return fread(data, len, 1, file) == 1;
}

bool TXL_File::write(void *data, const int len) {
  return fwrite(data, len, 1, file) == 1;
}

void TXL_File::close() {
  if (file) fclose(file);
  file = nullptr;
}