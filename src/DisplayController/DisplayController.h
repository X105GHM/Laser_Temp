#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <stdint.h>
#include <TM1637TinyDisplay.h>

class DisplayController {
public:

    DisplayController(uint8_t clkPin, uint8_t dioPin);

    void updateDisplay(float temperature, float batteryVoltage, bool showTemperature);

    void setBrightness(uint8_t brightness);

    uint8_t getBrightness() const noexcept { return brightness; }

private:
    TM1637TinyDisplay display;
    uint8_t brightness;
};

#endif // DISPLAY_CONTROLLER_H
