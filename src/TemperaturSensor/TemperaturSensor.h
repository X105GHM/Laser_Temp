#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <stdint.h>

class TemperatureSensor
{
public:

    explicit TemperatureSensor(uint8_t pin) noexcept;
    float readTemperature() noexcept;

private:

    uint8_t sensorPin;

    static constexpr float BETA            = 3950.0f;
    static constexpr float R_REF           = 100000.0f;
    static constexpr float T0              = 23.0f + 273.15f; // 23°C in Kelvin
    static constexpr float R0              = 30070.0f;
    static constexpr float ADC_REF_VOLTAGE = 5.0f;
    static constexpr int   ADC_MAX_VALUE   = 1023;
};

#endif // TEMPERATURE_SENSOR_H
