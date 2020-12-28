#include <Arduino.h>
//#include <Encoder.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include "BasicStepperDriver.h"
#include "GyverEncoder.h"

static const int PIN_STEP = 3;
static const int PIN_DIR = 4;
static const int PIN_EN = 2;
//#define ENCODER_DO_NOT_USE_INTERRUPTS
#define RPM 250
#define MICROSTEP 1

#define MOTOR_STEPS 200

#define one_turn MICROSTEPS* MOTOR_STEPS
BasicStepperDriver motor(MOTOR_STEPS, PIN_DIR, PIN_STEP, PIN_EN);

#define CLK 7
#define DT 6
#define SW 5
Encoder enc1(CLK, DT, SW, TYPE2);

static const int PIN_ENCODER_CLK = 7;
static const int PIN_ENCODER_DT = 6;
// Encoder myEnc(PIN_ENCODER_DT, PIN_ENCODER_CLK);

LiquidCrystal_I2C* lcd = nullptr;

int lastUpdate = 0;

void initDisplay() {
  lcd = new LiquidCrystal_I2C(0x27, 16, 2);
  lcd->init();
  lcd->backlight();
  lcd->print("arduino");
  lcd->setCursor(8, 1);
  lcd->print("LCD 1602");
}

void writeDisplay() {
  if (lcd == nullptr) {
    return;
  }
  if (millis() - lastUpdate >= 1000) {
    lcd->setCursor(0, 1);
    lcd->print(motor.getRPM());
    lastUpdate = millis();
  }
}

void setup() {
  Wire.begin();
  // myEnc.write(RPM);
  Serial.begin(9600);
  Serial.println("init start");
  // motor.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED, 5000, 2000);
  // motor.setSpeedProfile(BasicStepperDriver::LINEAR_SPEED, 5000, 5000);
  motor.begin(RPM, MICROSTEP);
  motor.setEnableActiveState(LOW);

  Serial.println("init end");
  motor.enable();
  Serial.println("Start");
  motor.startMove(90000);
  initDisplay();

  enc1.setTickMode(AUTO);
}
long oldPosition = -999;

void loop() {
  unsigned w1;

  w1 = motor.nextAction();

  if (w1 > 0) {
  } else {
    motor.disable();
    delay(100000);
  }

  if (enc1.isRight()) {
    Serial.println("Right");  // если был поворот
  }
  if (enc1.isLeft()) {
    Serial.println("Left");
  }

  if (enc1.isRightH()) {
    Serial.println("Right holded");  // если было удержание + поворот
  }
  if (enc1.isLeftH()) {
    Serial.println("Left holded");
  }

  if (enc1.isPress()) {
    Serial.println("Press");  // нажатие на кнопку (+ дебаунс)
  }
  if (enc1.isRelease()) {
    Serial.println("Release");  // отпускание кнопки (+ дебаунс)
  }
  if (enc1.isHolded()) {
    Serial.println("Holded");  // если была удержана и энк не поворачивался
  }
  /*   long newPosition = myEnc.read();
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
      motor.stop();
      motor.begin(newPosition, MICROSTEP);
      motor.startMove(90000);
      Serial.println(newPosition);
    } */

  writeDisplay();
}
