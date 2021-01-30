#include "Display.hpp"
#include "Motor.hpp"
#include "TemperaturePid.hpp"
#include "TemperatureSensor.hpp"
#include "TemperatureValueHolder.hpp"
#include "Values.hpp"
//#include "GyverTimers.h"
#include <TimerOne.h>

TemperatureValueHolder temperatureValueHolder;

Values values;
Display display(&values);
Motor motor(&values);
TemperatureSensor temperatureSensor;
TemperaturePid temperaturePid(&values);
unsigned long currentMillis = 0;

//void tickMotor() { motor.update(); }

void setup() {
  Serial.begin(9600);
  Serial.println("[Main] Start");
  Serial.println("[Main] Init start");
  values.addObserver(&motor);
  values.addObserver(&temperaturePid);
  motor.init();
  display.init();
  temperatureSensor.init(&temperatureValueHolder);
  temperaturePid.init(&temperatureValueHolder);
  Serial.println("[Main] Init end");

 // Timer1.initialize(1000000.0  / 250);
 // Timer1.attachInterrupt(tickMotor);
}



void loop() {
  currentMillis = millis();
  // motor.update();
  display.update();
  temperatureSensor.update(currentMillis);
  temperaturePid.update(currentMillis);
}
