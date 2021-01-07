#ifndef Display_HPP
#define Display_HPP

#include "Config.hpp"
#include "GyverEncoder.h"
#include "Values.hpp"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//#define ENCODER_DO_NOT_USE_INTERRUPTS

#define MENU_LINES 2 // количество строк дисплея

enum SettingsType { BOOL = 0, INT = 1 };

class Display {
private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
  Encoder encoder =
      Encoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, PIN_ENCODER_SW, TYPE2);

  // int vals[MENU_SETTINGS_AMOUNT]; // массив параметров

  Values *values;

  int8_t arrowPos = 0;
  int8_t screenPos = 0; // номер "экрана"

  // названия параметров
  const char *settingsNames[MENU_SETTINGS_AMOUNT] = {"Run", "Speed"};

  //типы параметров 0 - bool 1- int
  const SettingsType settingsType[MENU_SETTINGS_AMOUNT] = {SettingsType::BOOL,
                                                           SettingsType::INT};

public:
  Display(Values *values);
  ~Display();
  void init();
  void render();
  void update();
  void updateValue();
};

Display::Display(Values *values) { this->values = values; }

Display::~Display() {}

void Display::init() {
  Wire.begin();
  encoder.setTickMode(AUTO);
  lcd.init();
  lcd.backlight();
  render();
}

void Display::update() {

  encoder.tick();
  bool needUpdate = false;

  if (encoder.isTurn()) {
    // encoder.
    Serial.println("[Display] isTurn or isPress");
    int increment = 0; // локальная переменная направления

    // получаем направление
    if (encoder.isRight()) {
      increment = 1;
      needUpdate = true;
    }
    if (encoder.isLeft()) {
      increment = -1;
      needUpdate = true;
    }
    arrowPos += increment; // двигаем курсор
    arrowPos = constrain(arrowPos, 0, MENU_SETTINGS_AMOUNT - 1); // ограничиваем

    increment = 0;
    if (encoder.isRightH() && settingsType[arrowPos] == SettingsType::INT) {
      increment = -1;
      needUpdate = true;
      values->set(arrowPos,
                  values->get(arrowPos) + increment); // меняем параметры
    }
    if (encoder.isLeftH() && settingsType[arrowPos] == SettingsType::INT) {
      increment = 1;
      needUpdate = true;
      values->set(arrowPos,
                  values->get(arrowPos) + increment); // меняем параметры
    }
  }

  if (encoder.isPress()) { /// нажатие если параметр булевый инвертируем его
    SettingsType type = settingsType[arrowPos];
    Serial.print("[Display] settingsType type ");
    Serial.print(type);
    Serial.print(" arrowPos ");
    Serial.println(arrowPos);
    if (type == SettingsType::BOOL) {
      //  vals[arrowPos] = vals[arrowPos] == 1 ? 0 : 1;

      values->set(arrowPos, values->get(arrowPos) == 1 ? 0 : 1);

      needUpdate = true;
    }
  }

  if (needUpdate) {
    render();
  }
}
void Display::updateValue() {}

void Display::render() {
  lcd.clear();
  screenPos = arrowPos / MENU_LINES; // ищем номер экрана (0..3 - 0, 4..7 - 1)

  for (byte i = 0; i < MENU_LINES; i++) { // для всех строк
    lcd.setCursor(0, i);                  // курсор в начало

    // если курсор находится на выбранной строке
    if (arrowPos == MENU_LINES * screenPos + i)
      lcd.write(126); // рисуем стрелку
    else
      lcd.write(32); // рисуем пробел

    // если пункты меню закончились, покидаем цикл for
    if (MENU_LINES * screenPos + i == MENU_SETTINGS_AMOUNT)
      break;

    // выводим имя и значение пункта меню
    lcd.print(settingsNames[MENU_LINES * screenPos + i]);
    lcd.print(": ");
    lcd.print(values->get(MENU_LINES * screenPos + i));
  }
  /*
  if (encoder.isRight())
  {
      Serial.println("Right"); // если был поворот
  }
  if (encoder.isLeft())
  {
      Serial.println("Left");
  }

  if (encoder.isRightH())
  {
      Serial.println("Right holded"); // если было удержание + поворот
  }
  if (encoder.isLeftH())
  {
      Serial.println("Left holded");
  }

  if (encoder.isPress())
  {
      Serial.println("Press"); // нажатие на кнопку (+ дебаунс)
  }
  if (encoder.isRelease())
  {
      Serial.println("Release"); // отпускание кнопки (+ дебаунс)
  }
  if (encoder.isHolded())
  {
      Serial.println("Holded"); // если была удержана и энк не поворачивался
  }

  if (millis() - lastUpdate >= 1000)
  {
      lcd.setCursor(0, 1);
      lcd.print(motor.getRPM());
      lastUpdate = millis();
  } */
}

#endif