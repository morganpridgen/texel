#ifndef texel_ctrlh
#define texel_ctrlh
#include <SDL2/SDL.h>
#include <TEXEL/os.h>

enum TXL_CtrlButton {
  CtrlN = 0b1,
  CtrlS = 0b10,
  CtrlE = 0b100,
  CtrlW = 0b1000,
  CtrlStart = 0b10000,
  CtrlSelect = 0b100000,
  CtrlL = 0b1000000,
  CtrlR = 0b10000000,
  #if OS == linux || OS == windows // assume xbox controller
    CtrlA = 0b10,
    CtrlB = 0b100,
    CtrlX = 0b1000,
    CtrlY = 0b1,
  #endif // add nintendo switch variant?
  CtrlM = 0b100000000,
  CtrlNone = 0b0
};

class TEXELFunc TXL_Controller {
  protected:
    float aX;
    float aY;
    float mX;
    float mY;
    int b;
    int lB;
    int id;
  public:
    virtual bool init() = 0;
    virtual bool update() = 0;
    virtual void end() = 0;
    virtual bool isKeyboard() = 0;
    
    bool buttonPress(TXL_CtrlButton button) {return b & button;}
    bool buttonClick(TXL_CtrlButton button) {return (b & button) && (~lB & button);}
    bool buttonRelease(TXL_CtrlButton button) {return (~b & button) && (lB & button);}
    float leftJoyX() {return aX;}
    float leftJoyY() {return aY;}
    float mouseX() {return mX;}
    float mouseY() {return mY;}
    int getId() {return id;}
    virtual void rumble(float, int) = 0;
};

class TEXELFunc TXL_Gamepad : public TXL_Controller {
  protected:
    SDL_GameController *ctrl;
  public:
    virtual bool init();
    virtual bool update();
    virtual void end();
    virtual bool isKeyboard() {return 0;}
    
    virtual void rumble(float, int);
};

class TEXELFunc TXL_Keyboard : public TXL_Controller {
  public:
    virtual bool init();
    virtual bool update();
    virtual void end();
    virtual bool isKeyboard() {return 1;}
    
    virtual void rumble(float power, int time) {}
};

void TEXELFunc TXL_ManageController(TXL_Controller*&);

#endif