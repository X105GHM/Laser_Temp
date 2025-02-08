#include "DisplayController.h"
#include "HelpFunctions/utils.h"

DisplayController::DisplayController(uint8_t clkPin, uint8_t dioPin)
    : display(clkPin, dioPin), brightness(7)
{
    display.setBrightness(brightness);
}

void DisplayController::updateDisplay(float temperature, float batteryVoltage, bool showTemperature)
{
    if (showTemperature)
    {
        if (my_isnan(temperature))
        {
            const uint8_t ErrChars[] = {0x79, 0x50, 0x50, 0x00}; // "Err"
            display.setSegments(ErrChars);
            return;
        }
        int displayValue = static_cast<int>(temperature * 100);
        display.showNumberDec(displayValue, true);
    }
    else
    {
        if (my_isnan(batteryVoltage))
        {
            const uint8_t DashChars[] = {0x40, 0x40, 0x40, 0x40}; // "----"
            display.setSegments(DashChars);
            return;
        }
        int displayValue = static_cast<int>(batteryVoltage * 100);
        display.showNumberDec(displayValue, true);
    }
}

void DisplayController::setBrightness(uint8_t newBrightness)
{
    brightness = newBrightness;
    display.setBrightness(brightness);
}