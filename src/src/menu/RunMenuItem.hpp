#ifndef RunMenuItem_HPP
#define RunMenuItem_HPP

#include "MenuItem.hpp"
class RunMenuItem : public MenuItem {
private:
  Values *values;

public:
  RunMenuItem(Values *values);
  ~RunMenuItem();
  virtual void draw(LiquidCrystal_I2C &lcd) const override;
  virtual void event(Event event) const override;
};

RunMenuItem::RunMenuItem(Values *values) { this->values = values; }

RunMenuItem::~RunMenuItem() {}

void RunMenuItem::draw(LiquidCrystal_I2C &lcd) const {
  lcd.print("Run: ");

  if (values->get(MOTOR_ENABLED)) {
    lcd.write(arrowTopId);
  }
  lcd.print(values->get(MOTOR_SPEED));
}

void RunMenuItem::event(Event event) const {
  switch (event) {
  case Event::CLICK:
    if (!values->get(MOTOR_UNWIND_ENABLED)) {
      values->set(MOTOR_ENABLED, values->get(MOTOR_ENABLED) == 1 ? 0 : 1);
    }
    break;
  case Event::LEFT_HOLD: {
    values->set(MOTOR_SPEED, values->get(MOTOR_SPEED) + 1);
    break;
  }
  case Event::RIGHT_HOLD: {
    values->set(MOTOR_SPEED, values->get(MOTOR_SPEED) - 1);
    break;
  }

  default:
    break;
  }
}

#endif