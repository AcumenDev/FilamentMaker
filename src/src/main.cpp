#include <Arduino.h>
#include "Values.hpp"

#include "Display.hpp"
#include "Motor.hpp"

Values values;
Display display(&values);
Motor motor(&values);

int lastUpdate = 0;

void setup() {

  // myEnc.write(RPM);
  Serial.begin(9600);
  Serial.println("Start");
  Serial.println("init start");
  // motor.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED, 5000, 2000);
  // motor.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED, 5000, 5000);
  /// motor.begin(RPM, MICROSTEP);
  // motor.setEnableActiveState(LOW);
  values.addObserver(&motor);

  motor.init();
  display.init();
  Serial.println("init end");
}
long oldPosition = -999;

void loop() {
  motor.update();
  display.update();
}
