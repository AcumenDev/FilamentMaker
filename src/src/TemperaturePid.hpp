#ifndef TemperaturePid_hpp
#define TemperaturePid_hpp

#include "Config.hpp"
#include "IntervalWorkerBase.hpp"
#include "TemperatureValueHolder.hpp"
#include <Arduino.h>
#include <PID_v1.h>

class TemperaturePid : public IntervalWorkerBase, public Observer {
private:
  // Define Variables we'll be connecting to
  double setPoint = 0, output;

  // Specify the links and initial tuning parameters
  const double Kp = 14, Ki = 0.93, Kd = 59.87;
  PID *pid;
  TemperatureValueHolder *temperatureValueHolder;
  Values *values;

public:
  TemperaturePid(Values *values);
  ~TemperaturePid();
  void init(TemperatureValueHolder *temperatureValueHolder);
  void work(const unsigned long &currentMillis) override;
  void update(const unsigned long &currentMillis) override;
  void event(int index, int value) override;
};

TemperaturePid::TemperaturePid(Values *values) : IntervalWorkerBase(1000) {
  this->values = values;
}

TemperaturePid::~TemperaturePid() {}

void TemperaturePid::init(TemperatureValueHolder *temperatureValueHolder) {
  pinMode(PIN_PWM_HEAD, OUTPUT);
  this->temperatureValueHolder = temperatureValueHolder;
  setPoint = values->get(ParametrIndex::HEATER_TEMPERATURE);
  pid = new PID(temperatureValueHolder->get(), &output, &setPoint, Kp, Ki, Kd,
                DIRECT);
  pid->SetSampleTime(_interval);
  pid->SetMode(AUTOMATIC);
}
void TemperaturePid::work(const unsigned long &currentMillis) {}
void TemperaturePid::update(const unsigned long &currentMillis) {

  if (!values->get(ParametrIndex::HEATER_ENABLED)) {
    analogWrite(PIN_PWM_HEAD, 0);
    return;
  }

  if (pid->Compute()) {
    analogWrite(PIN_PWM_HEAD, output);
  }
  /*   Serial.print("[TemperaturePid] input: ");
    Serial.print(*(temperatureValueHolder->get()));
    Serial.print(" setPoint: ");
    Serial.print(setPoint);
    Serial.print(" output: ");
    Serial.println(output); */
}

void TemperaturePid::event(int index, int value) {
  Serial.print("[TemperaturePid] on event: Index ");
  Serial.print(index);
  Serial.print(" Value ");
  Serial.println(value);
  if (index == ParametrIndex::HEATER_TEMPERATURE) {
    this->setPoint = value;
  }
}

#endif