#include "FanController.h"

FanController::FanController(uint8_t pin) : pwmPin(pin), lastTemperature(0)
{
    pinMode(pwmPin, OUTPUT);
}

void FanController::updatePWMWithHysteresis(float temperature)
{
    uint8_t pwmValue;

    if (temperature >= TEMP_MAX)
    {
        pwmValue = PWM_MAX;
    }
    else if (temperature <= TEMP_MIN)
    {
        pwmValue = PWM_MIN;
    }
    else
    {
        if (temperature > lastTemperature + HYSTERESIS)
        {
            pwmValue = map(temperature, TEMP_MIN, TEMP_MAX, PWM_MIN, PWM_MAX);
        }
        else if (temperature < lastTemperature - HYSTERESIS)
        {
            pwmValue = map(temperature, TEMP_MIN, TEMP_MAX, PWM_MIN, PWM_MAX);
        }
        else
        {
            return;
        }
    }

    analogWrite(pwmPin, pwmValue);
    lastTemperature = temperature;
}
