#include "FanController.h"
#include <math.h>

static inline uint8_t mapValue(float x, float in_min, float in_max, uint8_t out_min, uint8_t out_max)
{
    if (x <= in_min)
        return out_min;
    if (x >= in_max)
        return out_max;
    return static_cast<uint8_t>((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

FanController::FanController(uint8_t pin) noexcept
    : pwmPin(pin), lastTemperature(TEMP_MIN), pwmDisabled(false)
{
    DDRB |= (1 << pwmPin);
}

void FanController::updatePWMWithHysteresis(float temperature) noexcept
{
    uint8_t newPWMValue = 0;

    if (temperature < TEMP_MIN)
    {
        newPWMValue = 0;
    }
    else if (temperature >= TEMP_MAX)
    {
        newPWMValue = PWM_MAX;
    }
    else
    {
        newPWMValue = mapValue(temperature, TEMP_MIN, TEMP_MAX, PWM_MIN, PWM_MAX);
    }

    if (newPWMValue > 0 && pwmDisabled)
    {
        initTimer0PWM();
        DDRB |= (1 << PB0);
        pwmDisabled = false;
    }

    if (!pwmDisabled)
    {
        if (fabs(temperature - lastTemperature) < HYSTERESIS && OCR0A == newPWMValue)
        {
            lastTemperature = temperature;
            return;
        }
    }

    if (newPWMValue == 0)
    {

        if (!pwmDisabled)
        {
            TCCR0A &= ~(1 << COM0A1);
            PORTB &= ~(1 << PB0);
            pwmDisabled = true;
        }
    }
    else
    {
        OCR0A = newPWMValue;
    }

    lastTemperature = temperature;
}