#include "Values.hpp"
#include "Display.hpp"
#include "Motor.hpp"
#include "TemperatureSensor.hpp"

Values values;
Display display(&values);
Motor motor(&values);
TemperatureSensor temperatureSensor;

unsigned long currentMillis = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("[Main] Start");
  Serial.println("[Main] Init start");
  values.addObserver(&motor);

  motor.init();
  display.init();
  temperatureSensor.init();

  Serial.println("[Main] Init end");
}

void loop() {
  currentMillis = millis();
  motor.update();
  display.update();
  temperatureSensor.update(currentMillis);
}
