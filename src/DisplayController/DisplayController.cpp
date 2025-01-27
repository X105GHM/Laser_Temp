#include "DisplayController.h"

DisplayController::DisplayController(uint8_t clkPin, uint8_t dioPin) : display(clkPin, dioPin)
{
    display.setBrightness(7);
}

void DisplayController::updateDisplay(float temperature, float batteryVoltage)
{
    unsigned long currentMillis = millis();
    if (currentMillis - lastDisplaySwitch >= displaySwitchInterval)
    {
        lastDisplaySwitch = currentMillis;
        showTemperature = !showTemperature;
    }

    if (showTemperature)
    {
        display.showNumberDecEx(int(temperature * 10), 0x80, false);
    }
    else
    {
        display.showNumberDec(int(batteryVoltage * 10), false);
    }
}

void DisplayController::blinkDisplay(unsigned long currentMillis, unsigned long blinkInterval, bool &blinkState)
{
    if (currentMillis - lastDisplaySwitch >= blinkInterval)
    {
        lastDisplaySwitch = currentMillis;
        blinkState = !blinkState;
        display.setBrightness(blinkState ? 7 : 0);
    }
}

void DisplayController::setBrightness(uint8_t brightness)
{
    display.setBrightness(brightness);
}
