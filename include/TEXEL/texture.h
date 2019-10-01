#ifndef texel_textureh
#define texel_textureh

#include <SDL2/SDL.h>
#include <TEXEL/os.h>

class TEXELFunc TXL_Texture {
  private:
    SDL_Texture *texture;
    float tW;
    float tH;
    float iW;
    float iH;
    float cL;
    float cR;
    float cT;
    float cB;
  public:
    TXL_Texture();
    bool loaded() {return texture != nullptr;}
    bool load(SDL_Surface*, int, int);
    bool load(const char[], int, int);
    bool load(const char path[]) {return load(path, -1, -1);}
    void free();
    void render(float, float, float, float, float); // x, y, sX, sY, r
    void render(float, float, float, float); // x, y, sX, sY
    void render(float x, float y, float r) {render(x, y, 1, 1, r);}
    void render(float x, float y) {render(x, y, 1, 1);}
    void setClip(float, float, float, float); // l, r, t, b
    void setColorMod(float, float, float); // r, g, b
    void setColorMod(float); // a
    void setColorMod(float r, float g, float b, float a) {setColorMod(r, g, b); setColorMod(a);}
    float width() {return iW;}
    float height() {return iH;}
};

#endif