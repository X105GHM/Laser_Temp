#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include <Arduino.h>

class FanController
{
public:
    FanController(uint8_t pin);
    void updatePWMWithHysteresis(float temperature);

private:
    uint8_t pwmPin;
    float lastTemperature;
    static constexpr uint8_t PWM_MIN = 0;
    static constexpr uint8_t PWM_MAX = 255;
    static constexpr float TEMP_MIN = 30.0;
    static constexpr float TEMP_MAX = 60.0;
    static constexpr float HYSTERESIS = 3.0;
};

#endif
