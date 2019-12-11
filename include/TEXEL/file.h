#ifndef texel_fileh
#define texel_fileh
#include <stdio.h>
#include <TEXEL/os.h>

void TEXELFunc TXL_InitPaths(const char*);
char* TEXELFunc TXL_DataPath(const char*);
char* TEXELFunc TXL_SavePath(const char*);
void TEXELFunc TXL_InitEndian();

class TEXELFunc TXL_File {
  private:
    FILE *file;
  public:
    TXL_File() {file = nullptr;}
    bool init(const char*, const char);
    bool read(void*, const int);
    bool write(void*, const int);
    void close();
};

bool TEXELFunc TXL_IsFile(const char*);
bool TEXELFunc TXL_IsDir(const char*);
bool TEXELFunc TXL_CreateDir(const char*);
bool TEXELFunc TXL_RemoveFile(const char*);
bool TEXELFunc TXL_RemoveDir(const char*);

#endif