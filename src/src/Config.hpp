#ifndef Config_HPP
#define Config_HPP
#include <Arduino.h>

static const int PIN_ENCODER_CLK = 7;
static const int PIN_ENCODER_DT = 6;
static const int PIN_ENCODER_SW = 5;

static const short PIN_DRIVER_STEP = 3;
static const short PIN_DRIVER_DIR = 4;
static const short PIN_DRIVER_EN = 2;

static const short PIN_TEMPERATURE = A0;

static const int MENU_SETTINGS_AMOUNT = 2; // количество настроек

#endif