#ifndef Motor_HPP
#define Motor_HPP
#include "Config.hpp"
#include "MotorDriver.hpp"
#include "Observer.hpp"
#define MICROSTEP 1

static const short MOTOR_STEPS = 200;

#define one_turn MICROSTEPS *MOTOR_STEPS

class Motor : public Observer {
private:
  MotorDriver motor =
      MotorDriver(PIN_DRIVER_STEP, PIN_DRIVER_DIR, PIN_DRIVER_EN);
  Values *values;

public:
  Motor(Values *values);
  void init();
  virtual ~Motor();
  void update();
  void event(int idex, int value) override;
  void run(int rpm, Direction dir);
};

Motor::Motor(Values *values) { this->values = values; }

Motor::~Motor() {}

void Motor::init() { motor.init(); }

void Motor::update() {}

void Motor::event(int index, int value) {
  Serial.print("[Motor] on event: Index ");
  Serial.print(index);
  Serial.print(" Value ");
  Serial.println(value);

  switch (index) {
  case ParametrIndex::MOTOR_ENABLED: {
    if (value) {
      run(values->get(ParametrIndex::MOTOR_SPEED), Forward);
    } else {
      motor.stop();
    }
    break;
  }
  case ParametrIndex::MOTOR_SPEED: {
    if (values->get(ParametrIndex::MOTOR_ENABLED)) {
      run(value, Forward);
    }
    break;
  }


  case ParametrIndex::MOTOR_UNWIND_ENABLED: {
    if (value) {
      run(values->get(ParametrIndex::MOTOR_UNWIND_SPEED), Backwards);
    } else {
      motor.stop();
    }
    break;
  }

  case ParametrIndex::MOTOR_UNWIND_SPEED: {
    if (values->get(ParametrIndex::MOTOR_UNWIND_ENABLED)) {
      run(value, Backwards);
    }
    break;
  }
  }

  // if (index == ParametrIndex::MOTOR_ENABLED) {
  //   if (value) {
  //     run(values->get(ParametrIndex::MOTOR_SPEED), Forward);
  //   } else {
  //     motor.stop();
  //   }
  // } else if (ParametrIndex::MOTOR_SPEED == index) {
  //   if (values->get(ParametrIndex::MOTOR_ENABLED)) {
  //     run(value, Forward);
  //   }
  // }

  // if (index == ParametrIndex::MOTOR_UNWIND_ENABLED) {
  //   if (value) {
  //     run(values->get(ParametrIndex::MOTOR_UNWIND_SPEED), Backwards);
  //   } else {
  //     motor.stop();
  //   }
  // } else if (ParametrIndex::MOTOR_UNWIND_SPEED == index) {
  //   if (values->get(ParametrIndex::MOTOR_UNWIND_ENABLED)) {
  //     run(value, Backwards);
  //   }
  // }
}

void Motor::run(int rpm, Direction dir) {
  motor.setDirection(dir);
  motor.start(rpm);
}

#endif