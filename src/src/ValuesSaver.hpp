#ifndef ValuesSaver_hpp
#define ValuesSaver_hpp
#include "EEPROMUtils.hpp"
#include "Observer.hpp"
#include "Values.hpp"
#include <Arduino.h>



class ValuesSaver : public Observer {
private:
public:
  ValuesSaver();
  ~ValuesSaver();
  void init();
  void event(int index, int value) override;
};

ValuesSaver::ValuesSaver() {}
ValuesSaver::~ValuesSaver() {}

void ValuesSaver::init() {

  uint8_t initFlag = 0;
  EEPROM_readAnything(EEPROM_ADR_INIT_FLAG, initFlag);
  if (initFlag!=97) {
    EEPROM_writeAnything(EEPROM_ADR_HEATER_TEMPERATURE, 200);
    EEPROM_writeAnything(EEPROM_ADR_MOTOR_SPEED, 200);
    EEPROM_writeAnything(EEPROM_ADR_MOTOR_UNWIND_SPEED, 300);
    EEPROM_writeAnything(EEPROM_ADR_INIT_FLAG, 97);
  }
}

void ValuesSaver::event(int index, int value) {
  Serial.print("[ValuesSaver] on event: Index ");
  Serial.print(index);
  Serial.print(" Value :");
  Serial.println(value);

  switch (index) {
  case ParametrIndex::HEATER_TEMPERATURE: {
    EEPROM_writeAnything(EEPROM_ADR_HEATER_TEMPERATURE, value);
    break;
  }
  case ParametrIndex::MOTOR_SPEED: {
    EEPROM_writeAnything(EEPROM_ADR_MOTOR_SPEED, value);
    break;
  }
  case ParametrIndex::MOTOR_UNWIND_SPEED: {
    EEPROM_writeAnything(EEPROM_ADR_MOTOR_UNWIND_SPEED, value);
    break;
  }
  }
}

#endif