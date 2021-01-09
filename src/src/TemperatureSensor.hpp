#ifndef TemperatureSensor_HPP
#define TemperatureSensor_HPP
#include "Config.hpp"
#include "IntervalWorkerBase.hpp"
#include <Arduino.h>

class TemperatureSensor : public IntervalWorkerBase {
private:
  static const int B = 3950; // B-коэффициент
  static const unsigned long SERIAL_R =
      102000; // сопротивление последовательного резистора, 102 кОм
  static const unsigned long THERMISTOR_R =
      100000; // номинальное сопротивления термистора, 100 кОм
  static const int NOMINAL_T =
      25; // номинальная температура (при которой TR = 100 кОм)

public:
  TemperatureSensor();
  ~TemperatureSensor();
  void init();
  void work( unsigned long currentMillis) override;
};

TemperatureSensor::TemperatureSensor() : IntervalWorkerBase(10000) {}

TemperatureSensor::~TemperatureSensor() {}

void TemperatureSensor::init() { pinMode(PIN_TEMPERATURE, INPUT); }
void TemperatureSensor::work( unsigned long currentMillis) {
  int t = analogRead(PIN_TEMPERATURE);
  float tr = 1023.0 / t - 1;
  tr = SERIAL_R / tr;
  Serial.print("[TemperatureSensor] R=");
  Serial.print(tr);
  Serial.print(", t=");

  float steinhart;
  steinhart = tr / THERMISTOR_R;           // (R/Ro)
  steinhart = log(steinhart);              // ln(R/Ro)
  steinhart /= B;                          // 1/B * ln(R/Ro)
  steinhart += 1.0 / (NOMINAL_T + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;             // Invert
  steinhart -= 273.15;
  Serial.println(steinhart);
}
#endif