#ifndef StopSensor_hpp
#define StopSensor_hpp
#include "Arduino.h"
#include "IntervalWorkerBase.hpp"
#include "Values.hpp"

class StopSensor : public IntervalWorkerBase {
private:
  Values *values;

public:
  StopSensor(Values *values);
  ~StopSensor();
  void init();
  void work(const unsigned long &currentMillis) override;
};

StopSensor::StopSensor(Values *values) : IntervalWorkerBase(500) {
  this->values = values;
}

StopSensor::~StopSensor() {}

void StopSensor::init() { pinMode(PIN_STOP_SENSOR, INPUT_PULLUP); }

void StopSensor::work(const unsigned long &currentMillis) {
  if (!digitalRead(PIN_STOP_SENSOR)) {
    values->set(MOTOR_ENABLED, 0);
    values->set(HEATER_ENABLED, 0);
  }
}
#endif