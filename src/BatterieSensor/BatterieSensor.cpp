#include "BatterieSensor/BatterieSensor.h"
#include "HelpFunctions/utils.h"
#include <avr/io.h>
#include <util/delay.h>

BatterySensor::BatterySensor(uint8_t pin) noexcept
    : sensorPin(pin)
{
    DDRB &= ~(1 << sensorPin);
}

float BatterySensor::readBatteryVoltage() noexcept
{
    uint16_t adcValue = readADC(2);

    if (adcValue == 0 || adcValue >= ADC_MAX_VALUE)
        return 0.00f;

    float voltage = (adcValue * ADC_REF_VOLTAGE) / ADC_MAX_VALUE;
    return (voltage * VOLTAGE_DIVIDER_RATIO) + 0.17f;
}
