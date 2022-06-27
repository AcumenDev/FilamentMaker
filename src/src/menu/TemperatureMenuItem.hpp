#ifndef TemperatureMenuItem_hpp
#define TemperatureMenuItem_hpp
#include "MenuItem.hpp"
#include "TemperatureValueHolder.hpp"
#include "Values.hpp"
class TemperatureMenuItem : public MenuItem {
private:
  Values *values;

  TemperatureValueHolder *currentTemperature;

public:
  TemperatureMenuItem(Values *values,
                      TemperatureValueHolder *currentTemperature);
  ~TemperatureMenuItem();

  virtual void draw(LiquidCrystal_I2C &lcd) const override;
  virtual void event(Event event) const override;
};

TemperatureMenuItem::TemperatureMenuItem(
    Values *values, TemperatureValueHolder *currentTemperature) {
  this->values = values;
  this->currentTemperature = currentTemperature;
}

TemperatureMenuItem::~TemperatureMenuItem() {}

void TemperatureMenuItem::draw(LiquidCrystal_I2C &lcd) const {
  lcd.print("Temp:");
  if (values->get(HEATER_ENABLED)) {
    lcd.write(arrowTopId);
  }
  lcd.print((int)(*currentTemperature->get()));
  lcd.write(126);
  lcd.print(values->get(HEATER_TEMPERATURE));
}

void TemperatureMenuItem::event(Event event) const {
  switch (event) {
  case Event::CLICK:
    values->set(HEATER_ENABLED, values->get(HEATER_ENABLED) == 1 ? 0 : 1);
    break;
case Event::LEFT_HOLD: {
    values->set(HEATER_TEMPERATURE, values->get(HEATER_TEMPERATURE) + 1);
    break;
  }
  case Event::RIGHT_HOLD: {
    values->set(HEATER_TEMPERATURE, values->get(HEATER_TEMPERATURE) - 1);
    break;
  }
  default:
    break;
  }
}

#endif