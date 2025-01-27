#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <Arduino.h>

class TemperatureSensor
{
public:
    TemperatureSensor(uint8_t pin);
    float readTemperature();

private:
    uint8_t sensorPin;
    static constexpr float BETA = 3950.0;
    static constexpr float R_REF = 100000.0;
    static constexpr float T0 = 25.0 + 273.15;
    static constexpr float R0 = 100000.0;
};

#endif
