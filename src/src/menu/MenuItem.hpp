#ifndef MenuItem_hpp
#define MenuItem_hpp
#include <LiquidCrystal_I2C.h>

enum Event { CLICK, LEFT_HOLD, RIGHT_HOLD };

byte arrowTopMask[8] = {0b00100, 0b01110, 0b10101, 0b00100,
                        0b00100, 0b00100, 0b00100, 0b00100};
uint8_t arrowTopId = 0;

class MenuItem {
private:
public:
  MenuItem();
  ~MenuItem();
  virtual void draw(LiquidCrystal_I2C &lcd) const = 0;
  virtual void event(Event event) const = 0;
};

MenuItem::MenuItem() {}

MenuItem::~MenuItem() {}

#endif