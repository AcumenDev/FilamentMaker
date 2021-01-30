#ifndef Motor_HPP
#define Motor_HPP
#include "BasicStepperDriver.h"
#include "Config.hpp"
#include "MotorDriver.hpp"
#include "Observer.hpp"
#define RPM 250
#define MICROSTEP 1

static const short MOTOR_STEPS = 200;

#define one_turn MICROSTEPS *MOTOR_STEPS

class Motor : public Observer {
private:
  // BasicStepperDriver motor = BasicStepperDriver(MOTOR_STEPS, PIN_DRIVER_DIR,
  //                                               PIN_DRIVER_STEP,
  //                                               PIN_DRIVER_EN);
  MotorDriver motor =
      MotorDriver(PIN_DRIVER_STEP, PIN_DRIVER_DIR, PIN_DRIVER_EN);
  Values *values;

public:
  Motor(Values *values);
  void init();
  virtual ~Motor();
  void update();
  void event(int idex, int value) override;
  void run(int rpm);
};

Motor::Motor(Values *values) { this->values = values; }

Motor::~Motor() {}

void Motor::init() {
  // motor.setEnableActiveState(LOW);
  // motor.disable();
  motor.init();
  Serial.print("[Motor] STEP_PULSE ");
  Serial.println(STEP_PULSE(MOTOR_STEPS, 1, 250));
  if (values->get(ParametrIndex::MOTOR_ENABLED)) {
    run(values->get(ParametrIndex::MOTOR_SPEED));
  }
}

void Motor::update() {

  // unsigned wait_time_micros;
  // wait_time_micros = motor.nextAction();
  // if (wait_time_micros <= 0) {
  //   // motor.disable();
  // }

  // if (wait_time_micros > 500) {
  //   motor.startMove(200 * 1000);
  // }
}

void Motor::event(int index, int value) {
  Serial.print("[Motor] on event: Index ");
  Serial.print(index);
  Serial.print(" Value ");
  Serial.println(value);
  if (index == ParametrIndex::MOTOR_ENABLED) {
    if (!value) {
      motor.stop();
    } else {
      run(values->get(ParametrIndex::MOTOR_SPEED));
    }
  } else if (ParametrIndex::MOTOR_SPEED == index) {
    if (values->get(ParametrIndex::MOTOR_ENABLED)) {
      run(value);
    }
  }
}

void Motor::run(int rpm) {
  /*  motor.begin(rpm, MICROSTEP);
   motor.startMove(200 * 1000); */
  motor.start(rpm);
}

#endif