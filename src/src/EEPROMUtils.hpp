#ifndef EEPROMUtils_hpp
#define EEPROMUtils_hpp
#include <EEPROM.h>

template <class T> int EEPROM_writeAnything(int ee, const T &value) {
  const byte *p = (const byte *)(const void *)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++) {
    EEPROM.update(ee++, *p++);
  }
  return i;
}

template <class T> int EEPROM_readAnything(int ee, T &value) {
  byte *p = (byte *)(void *)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++) {
    *p++ = EEPROM.read(ee++);
  }
  return i;
}

/*
struct config_t
{
    int mynumber1;
    int mynumber2;
    int mynumber3;
} configuration;

void setup()
{
    EEPROM_readAnything(0, configuration);
    Serial.begin(9600);       // use the serial port
    Serial.println(mynumber1, DEC);
    Serial.println(mynumber2, DEC);
    Serial.println(mynumber3, DEC);
    // ...
}
void loop()
{
    // let the user adjust their settings
    // I'll put values here to simulate user selected options
    mynumber1 = 1035;
    mynumber2 = 34;
    mynumber3 = 845;

    // if they push the "Save" button, save their configuration
    if (digitalRead(13) == HIGH)
        EEPROM_writeAnything(0, configuration);

}*/

#endif