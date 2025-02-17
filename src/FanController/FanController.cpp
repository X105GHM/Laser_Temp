#include "FanController.h"
#include <math.h>

FanController::FanController(uint8_t pin) noexcept
    : pwmPin(pin), lastTemperature(TEMP_MIN), pwmDisabled(true)
{
    DDRB |= (1 << pwmPin);
}

void FanController::updatePWMWithHysteresis(float temperature) noexcept
{
    if (isnan(temperature))
    {
        return;
    }

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

    if (!pwmDisabled && (fabs(temperature - lastTemperature) < HYSTERESIS) && (OCR0A == newPWMValue))
    {
        lastTemperature = temperature;
        return;
    }

    if (newPWMValue > 0)
    {
        if (pwmDisabled)
        {
            initTimer0PWM();
            DDRB |= (1 << PB0);
            pwmDisabled = false;
        }
        OCR0A = newPWMValue;
    }
    else
    {
        if (!pwmDisabled)
        {
            TCCR0A &= ~(1 << COM0A1);
            PORTB &= ~(1 << PB0);
            pwmDisabled = true;
        }
    }
    lastTemperature = temperature;
}