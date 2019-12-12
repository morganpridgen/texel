#ifndef texel_fileh
#define texel_fileh
#include <stdio.h>
#include <TEXEL/os.h>
#if OS == linux
  #include <netinet/in.h>
#elif OS == windows
  #include <winsock.h>
#endif

void TEXELFunc TXL_InitPaths(const char*);
char* TEXELFunc TXL_DataPath(const char*);
char* TEXELFunc TXL_SavePath(const char*);
void TEXELFunc TXL_InitEndian();
void TEXELFunc TXL_FlipEndian(void*, int);

class TEXELFunc TXL_File {
  private:
    FILE *file;
  public:
    TXL_File() {file = nullptr;}
    bool init(const char*, const char);
    int read(void*, const int);
    int write(void*, const int);
    void close();
};

bool TEXELFunc TXL_IsFile(const char*);
bool TEXELFunc TXL_IsDir(const char*);
bool TEXELFunc TXL_CreateDir(const char*);
bool TEXELFunc TXL_RemoveFile(const char*);
bool TEXELFunc TXL_RemoveDir(const char*);

class TEXELFunc TXL_Socket {
  private:
    #if OS == linux
      int s;
    #elif OS == windows
      SOCKET s;
    #endif
    sockaddr_in serverAddr;
  public:
    bool init(const char*);
    int read(void*, const int);
    int write(void*, const int);
    bool hasData();
    void end();
};
bool TXL_InitSocket();
void TXL_EndSocket();

#endif