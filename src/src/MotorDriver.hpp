#ifndef MotorDriver_hpp
#define MotorDriver_hpp
#include <Arduino.h>
#include <TimerOne.h>

class MotorDriver {
private:
  static short _pinStep;
  const short pinDir;
  const short pinEn;

  const int steps;
  const int microsteps;

  static void tickMotor();

public:
  MotorDriver(short pinStep, short pinDir, short pinEn, int steps = 200,
              int microsteps = 1);

  virtual ~MotorDriver() {}
  void init();
  void start(int rpm);
  void stop();

  static long getInterval(int rpm, int microsteps, int steps);
};

MotorDriver::MotorDriver(short pinStep, short pinDir, short pinEn, int steps,
                         int microsteps)
    : pinDir(pinDir), pinEn(pinEn), steps(steps), microsteps(microsteps) {

  _pinStep = pinStep;
}

void MotorDriver::init() {
  pinMode(_pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  pinMode(pinEn, OUTPUT);
  digitalWrite(_pinStep, LOW);
  digitalWrite(pinDir, LOW);
  digitalWrite(pinEn, HIGH);
  Timer1.attachInterrupt(MotorDriver::tickMotor);
}

void MotorDriver::start(int rpm) {
  Timer1.initialize(MotorDriver::getInterval(rpm, microsteps, steps));
    digitalWrite(pinEn, LOW);
}

void MotorDriver::stop() {
  Timer1.stop();
  digitalWrite(_pinStep, LOW);
  digitalWrite(pinDir, LOW);
  digitalWrite(pinEn, HIGH);
}
void MotorDriver::tickMotor() {
  digitalWrite(_pinStep, 1);
  delayMicroseconds(2);
  digitalWrite(_pinStep, 0);
}

long MotorDriver::getInterval(int rpm, int microsteps, int steps) {
  return 60.0 * 1000000L / steps / microsteps / rpm;
}
short MotorDriver::_pinStep;

#endif