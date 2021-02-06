#ifndef Menu_HPP
#define Menu_HPP

#include "Config.hpp"
#include "GyverEncoder.h"
#include "TimeUtils.hpp"
#include "Values.hpp"
#include "menu/MenuItem.hpp"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//#define ENCODER_DO_NOT_USE_INTERRUPTS

static const short MENU_LINES = 2; // количество строк дисплея
static const short MENU_ITEMS = 2; // количество опций
class Menu {
private:
  LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
  Encoder encoder =
      Encoder(PIN_ENCODER_CLK, PIN_ENCODER_DT, PIN_ENCODER_SW, TYPE2);

  int8_t arrowPos = 0;
  int8_t screenPos = 0; // номер "экрана"

  MenuItem **items;

  unsigned long _prev_ms = 0;

public:
  Menu(MenuItem **items);
  ~Menu();

  void init();
  void render();
  void update(const unsigned long &currentMillis);
};

Menu::Menu(MenuItem **items) { this->items = items; }

Menu::~Menu() {}

void Menu::init() {
  Wire.begin();
  encoder.setTickMode(AUTO);
  lcd.init();
  lcd.backlight();
  lcd.createChar(arrowTopId, arrowTopMask);
  render();
}

void Menu::update(const unsigned long &currentMillis) {

  encoder.tick();
  bool needUpdate = false;

  if (encoder.isTurn()) {

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
    arrowPos = constrain(arrowPos, 0, MENU_ITEMS - 1); // ограничиваем
  }

  if (encoder.isClick()) {
    items[arrowPos]->event(Event::CLICK);
    needUpdate = true;
  }

  if (encoder.isLeftH()) {
    items[arrowPos]->event(Event::LEFT_HOLD);
    needUpdate = true;
  }
  if (encoder.isRightH()) {
    items[arrowPos]->event(Event::RIGHT_HOLD);
    needUpdate = true;
  }

  if (TimeUtils::isWorkTime(_prev_ms, currentMillis, 1000)) {
    needUpdate = true;
    _prev_ms = currentMillis;
  }

  if (needUpdate) {
    render();
  }
}

void Menu::render() {
  lcd.clear();
  screenPos = arrowPos / MENU_LINES; // ищем номер экрана (0..3 - 0, 4..7 - 1)

  for (byte i = 0; i < MENU_LINES; i++) { // для всех строк
    lcd.setCursor(0, i);                  // курсор в начало

    // если курсор находится на выбранной строке
    if (arrowPos == MENU_LINES * screenPos + i) {
      lcd.write(126); // рисуем стрелку
    } else {
      lcd.write(32); // рисуем пробел
    }
    // если пункты меню закончились, покидаем цикл for
    if (MENU_LINES * screenPos + i == MENU_ITEMS) {
      break;
    }

    items[MENU_LINES * screenPos + i]->draw(lcd);
  }
}

#endif