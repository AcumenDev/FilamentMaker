#include "Menu.hpp"
#include "Motor.hpp"
#include "StopSensor.hpp"
#include "TemperaturePid.hpp"
#include "TemperatureSensor.hpp"
#include "TemperatureValueHolder.hpp"
#include "Values.hpp"
#include "ValuesSaver.hpp"
#include "menu/RunMenuItem.hpp"
#include "menu/TemperatureMenuItem.hpp"
#include "menu/UnwindMenuItem.hpp"

Values values;
ValuesSaver valuesSaver;
TemperatureValueHolder tempValueHolder;
Motor motor(&values);
TemperatureSensor temperatureSensor;
TemperaturePid temperaturePid(&values);
auto runMenuItem = RunMenuItem(&values);
auto tempMenuItem = TemperatureMenuItem(&values, &tempValueHolder);
auto unwindMenuItem = UnwindMenuItem(&values);
MenuItem *menus[MENU_ITEMS] = {&runMenuItem, &tempMenuItem, &unwindMenuItem};
Menu menu(menus);
StopSensor stopSensor(&values);

unsigned long currentMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("[Main] Start");
  Serial.println("[Main] Init start");
  valuesSaver.init();
  values.init();
  values.addObserver(&motor);
  values.addObserver(&temperaturePid);
  values.addObserver(&valuesSaver);
  motor.init();
  temperatureSensor.init(&tempValueHolder);
  temperaturePid.init(&tempValueHolder);
  menu.init();
  stopSensor.init();
  Serial.println("[Main] Init end");
}

void loop() {
  currentMillis = millis();
  temperatureSensor.update(currentMillis);
  temperaturePid.update(currentMillis);
  menu.update(currentMillis);
  stopSensor.update(currentMillis);
}
