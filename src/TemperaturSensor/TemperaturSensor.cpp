#include "TemperaturSensor/TemperaturSensor.h"
#include "HelpFunctions/utils.h"
#include <math.h>
#include <avr/io.h>

TemperatureSensor::TemperatureSensor(uint8_t pin) noexcept
    : sensorPin(pin)
{
    DDRB &= ~(1 << sensorPin);
}

float TemperatureSensor::readTemperature() noexcept
{

    const int adcValue = readADC(3);

    if (adcValue <= 0 || adcValue >= ADC_MAX_VALUE)
        return NAN;

    const float voltage = adcValue * (ADC_REF_VOLTAGE / ADC_MAX_VALUE);
    constexpr float epsilon = 1e-6f;
    if (voltage < epsilon)
        return NAN;

    const float resistance = (voltage * R_REF) / (ADC_REF_VOLTAGE - voltage);
    if (resistance <= 0.0f)
        return NAN;

    const float denominator = logf(resistance / R0) / BETA + (1.0f / T0);
    if (fabsf(denominator) < epsilon)
        return NAN;

    const float tempKelvin = 1.0f / denominator;
    const float tempCelsius = tempKelvin - 273.15f;
    return tempCelsius;
}
