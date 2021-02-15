#ifndef UnwindMenuItem_hpp
#define UnwindMenuItem_hpp
#include "MenuItem.hpp"
#include "Values.hpp"

class UnwindMenuItem : public MenuItem {
private:
  Values *values;

public:
  UnwindMenuItem(Values *values);
  ~UnwindMenuItem();
  virtual void draw(LiquidCrystal_I2C &lcd) const override;
  virtual void event(Event event) const override;
};

UnwindMenuItem::UnwindMenuItem(Values *values) { this->values = values; }
UnwindMenuItem::~UnwindMenuItem() {}

void UnwindMenuItem::draw(LiquidCrystal_I2C &lcd) const {
  lcd.print("Unwind: ");

  if (values->get(MOTOR_UNWIND_ENABLED)) {
    lcd.write(arrowTopId);
  }
  lcd.print(values->get(MOTOR_UNWIND_SPEED));
}

void UnwindMenuItem::event(Event event) const {
  switch (event) {
  case Event::CLICK:

    if (!values->get(MOTOR_ENABLED)) {
      values->set(MOTOR_UNWIND_ENABLED,
                  values->get(MOTOR_UNWIND_ENABLED) == 1 ? 0 : 1);
    }
    break;
  case Event::LEFT_HOLD: {
    values->set(MOTOR_UNWIND_SPEED, values->get(MOTOR_UNWIND_SPEED) + 1);
    break;
  }
  case Event::RIGHT_HOLD: {
    values->set(MOTOR_UNWIND_SPEED, values->get(MOTOR_UNWIND_SPEED) - 1);
    break;
  }

  default:
    break;
  }
}

#endif