#include "Display.hpp"
#include "Motor.hpp"
#include "TemperaturePid.hpp"
#include "TemperatureSensor.hpp"
#include "TemperatureValueHolder.hpp"
#include "Values.hpp"

TemperatureValueHolder temperatureValueHolder;

Values values;
Display display(&values);
Motor motor(&values);
TemperatureSensor temperatureSensor;
TemperaturePid temperaturePid(&values);
unsigned long currentMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("[Main] Start");
  Serial.println("[Main] Init start");
  values.addObserver(&motor);

  motor.init();
  display.init();
  temperatureSensor.init(&temperatureValueHolder);
  temperaturePid.init(&temperatureValueHolder);
  Serial.println("[Main] Init end");
}

void loop() {
  currentMillis = millis();
  motor.update();
  display.update();
  temperatureSensor.update(currentMillis);
  temperaturePid.update(currentMillis);
}
