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

char baseDir[256];
char savePath[256];
char dataPath[256];

char endian = 0;

void flipEndian(void*, int);

void TXL_InitPaths(const char *saveName) {
  char tmpPath[256];
  int i = 0;
  #if OS == linux
    tmpPath[readlink("/proc/self/exe", tmpPath, 256)] = 0;
    realpath(tmpPath, baseDir);
  #elif OS == windows
    tmpPath[GetModuleFileName(NULL, tmpPath, 256)] = 0;
    GetFullPathName(tmpPath, 256, baseDir, NULL);
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
  memset(tmpPath, 0, 256);
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
  static char out[256];
  memset(out, 0, 256);
  sprintf(out, "%s/%s", dataPath, file);
  return out;
}

char *TXL_SavePath(const char *file) {
  static char out[256];
  memset(out, 0, 256);
  sprintf(out, "%s/%s", savePath, file);
  return out;
}

void TXL_InitEndian() {
  int num = 1;
  endian = (((char *)&num)[0] == 0) ? 'B' : 'L';
  printf("System is %s endian.\n", endian == 'B' ? "bin" : "little");
}

void flipEndian(void *data, int size) {
  if (endian == 'L') {
    for (int i = 0; i < size / 2; i++) {
      ((char *)data)[i] ^= ((char *)data)[size - i - 1];
      ((char *)data)[size - i - 1] ^= ((char *)data)[i];
      ((char *)data)[i] ^= ((char *)data)[size - i - 1];
    }
  }
}



bool TXL_File::init(const char *path, const char mode) {
  close();
  char newMode[3];
  sprintf(newMode, "%cb", mode);
  file = fopen(path, newMode);
  return file != NULL;
}

bool TXL_File::read(void *data, const int len) {
  bool ok =  fread(data, len, 1, file) == 1;
  flipEndian(data, len);
  return ok;
}

bool TXL_File::write(void *data, const int len) {
  flipEndian(data, len);
  bool ok = fwrite(data, len, 1, file) == 1;
  flipEndian(data, len);
  return ok;
}

void TXL_File::close() {
  if (file) fclose(file);
  file = nullptr;
}



bool TXL_IsFile(const char *path) {
  #if OS == linux
    struct stat info;
    return stat(path, &info) == 0 && info.st_mode & S_IFREG;
  #elif OS == windows
    DWORD stat = GetFileAttributes(path);
    return stat == INVALID_FILE_ATTRIBUTES && GetLastError() != ERROR_FILE_NOT_FOUND && stat & FILE_ATTRIBUTE_NORMAL;
  #endif
}

bool TXL_IsDir(const char *path) {
  #if OS == linux
    struct stat info;
    return stat(path, &info) == 0 && info.st_mode & S_IFDIR;
  #elif OS == windows
    DWORD stat = GetFileAttributes(path);
    return stat == INVALID_FILE_ATTRIBUTES && GetLastError() != ERROR_FILE_NOT_FOUND && stat & FILE_ATTRIBUTE_DIRECTORY;
  #endif
}

bool TXL_CreateDir(const char *path) {
  if (TXL_IsFile(path) || TXL_IsDir(path)) return 0;
  #if OS == linux
    mkdir(path, 0700);
  #elif OS == windows
    CreateDirectory(path, NULL);
  #endif
}

bool TXL_RemoveFile(const char *path) {
  if (!TXL_IsFile(path)) return 0;
  #if OS == linux
    return unlink(path) == 0;
  #elif OS == windows
    return DeleteFile(path);
  #endif
}

bool TXL_RemoveDir(const char *path) {
  if (!TXL_IsDir(path)) return 0;
  #if OS == linux
    return rmdir(path) == 0;
  #elif OS == windows
    return DeleteDirectory(path);
  #endif
}