#ifndef Value_HPP
#define Value_HPP
#include "Config.hpp"
#include "EEPROMUtils.hpp"
#include "Observer.hpp"
enum ParametrIndex {

  MOTOR_ENABLED = 0,
  MOTOR_SPEED = 1,
  HEATER_ENABLED = 2,
  HEATER_TEMPERATURE = 3,
  MOTOR_UNWIND_ENABLED = 4,
  MOTOR_UNWIND_SPEED = 5,

};

class Values {
private:
  int vals[6]; // массив параметров

  static const int maxObservers = 5;
  Observer *observers[maxObservers];
  int currentObservers = 0;

  void notify(int index, int value);

public:
  Values();
  ~Values();

  void init();
  void set(int index, int value);
  int get(int index);

  bool addObserver(Observer *observer);
};

Values::Values() {}

Values::~Values() {}

void Values::init() {
  vals[MOTOR_ENABLED] = 0;
  vals[HEATER_ENABLED] = 0;
  vals[MOTOR_UNWIND_ENABLED] = 0;

  EEPROM_readAnything(EEPROM_ADR_MOTOR_SPEED, vals[MOTOR_SPEED]);
  EEPROM_readAnything(EEPROM_ADR_HEATER_TEMPERATURE, vals[HEATER_TEMPERATURE]);
  EEPROM_readAnything(EEPROM_ADR_MOTOR_UNWIND_SPEED, vals[MOTOR_UNWIND_SPEED]);
}

void Values::set(int index, int value) {
  vals[index] = value;
  notify(index, value);
}

int Values::get(int index) { return vals[index]; }

bool Values::addObserver(Observer *observer) {
  Serial.println("[Values] addObserver");
  if (maxObservers - 1 <= currentObservers) {
    return false;
  }

  observers[currentObservers] = observer;
  currentObservers++;
  Serial.print("[Values] Observers : ");
  Serial.println(currentObservers);
  return true;
}

void Values::notify(int index, int value) {
  Serial.println("[Values] notify");
  if (currentObservers <= 0) {
    return;
  }

  for (int i = 0; i < currentObservers; i++) {
    Serial.print("[Values] Observer event");
    Serial.println(i);
    observers[i]->event(index, value);
  }
}

#endif