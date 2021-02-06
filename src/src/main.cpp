#include "Display.hpp"
#include "Menu.hpp"
#include "Motor.hpp"
#include "TemperaturePid.hpp"
#include "TemperatureSensor.hpp"
#include "TemperatureValueHolder.hpp"
#include "Values.hpp"
#include "menu/RunMenuItem.hpp"
#include "menu/TemperatureMenuItem.hpp"

TemperatureValueHolder temperatureValueHolder;

Values values;

Motor motor(&values);
TemperatureSensor temperatureSensor;
TemperaturePid temperaturePid(&values);

RunMenuItem runMenuItem = RunMenuItem(&values);
TemperatureMenuItem temperatureMenuItem =
    TemperatureMenuItem(&values, &temperatureValueHolder);
MenuItem *menus[MENU_ITEMS] = {&runMenuItem, &temperatureMenuItem};
Menu menu(menus);

unsigned long currentMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("[Main] Start");
  Serial.println("[Main] Init start");
  values.addObserver(&motor);
  values.addObserver(&temperaturePid);
  motor.init();
  temperatureSensor.init(&temperatureValueHolder);
  temperaturePid.init(&temperatureValueHolder);
  menu.init();
  Serial.println("[Main] Init end");
}

void loop() {
  currentMillis = millis();
  temperatureSensor.update(currentMillis);
  temperaturePid.update(currentMillis);
  menu.update(currentMillis);
}
