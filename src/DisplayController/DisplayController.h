#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <Arduino.h>
#include <TM1637Display.h>

class DisplayController
{
public:
    DisplayController(uint8_t clkPin, uint8_t dioPin);
    void updateDisplay(float temperature, float batteryVoltage);
    void blinkDisplay(unsigned long currentMillis, unsigned long blinkInterval, bool &blinkState);
    void setBrightness(uint8_t brightness);

private:
    TM1637Display display;
    bool showTemperature = true;
    unsigned long lastDisplaySwitch = 0;
    constexpr static unsigned long displaySwitchInterval = 5000;
};

#endif
