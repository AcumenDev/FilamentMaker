#ifndef Value_HPP
#define Value_HPP
#include "Config.hpp"
#include "Observer.hpp"
////todo отвязать меню от параметров
enum ParametrIndex {

  MOTOR_ENABLED = 0,
  MOTOR_SPEED = 1,
  HEATER_ENABLED = 2,
  HEATER_TEMPERATURE = 3
};

enum SettingsType { BOOL = 0, INT = 1, FLOAT = 2 };
// названия параметров
const char *settingsNames[MENU_SETTINGS_AMOUNT] = {"Run", "Speed", "Heater",
                                                   "Temp"};

//типы параметров 0 - bool 1- int
const SettingsType settingsType[MENU_SETTINGS_AMOUNT] = {
    SettingsType::BOOL, SettingsType::INT, SettingsType::BOOL,
    SettingsType::FLOAT};

class Values {
private:
  int vals[MENU_SETTINGS_AMOUNT]; // массив параметров

  static const int maxObservers = 5;
  Observer *observers[maxObservers];
  int currentObservers = 0;

  void notify(int index, int value);

public:
  Values(/* args */);
  ~Values();

  void set(int index, int value);
  int get(int index);

  bool addObserver(Observer *observer);
};

Values::Values(/* args */) {
  vals[MOTOR_ENABLED] = 0;
  vals[MOTOR_SPEED] = 250;
  vals[HEATER_ENABLED] = 0;
  vals[HEATER_TEMPERATURE] = 240;
}

Values::~Values() {}

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