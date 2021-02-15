#ifndef Config_HPP
#define Config_HPP
#include <Arduino.h>

/// encoders pins
static const int PIN_ENCODER_CLK = 7;
static const int PIN_ENCODER_DT = 6;
static const int PIN_ENCODER_SW = 5;
///
/// motor driver pins
static const short PIN_DRIVER_STEP = 3;
static const short PIN_DRIVER_DIR = 4;
static const short PIN_DRIVER_EN = 2;
///
/// NTC Temperature sensor pin
static const short PIN_TEMPERATURE = A0;
/// mosfet pin
static const short PIN_PWM_HEAD = 9;
///

///StopSensor
static const short PIN_STOP_SENSOR = A1;
///


/// motor microstep
static const int MOTOR_MICRO_STEPS = 8;
///
/// PID temperature
static const double PID_KP = 14;
static const double PID_KI = 0.93;
static const double PID_KD = 59.87;
///







static const int EEPROM_ADR_INIT_FLAG = 0;
static const int EEPROM_ADR_HEATER_TEMPERATURE = 2;
static const int EEPROM_ADR_MOTOR_SPEED = 4;
static const int EEPROM_ADR_MOTOR_UNWIND_SPEED = 6;


#endif