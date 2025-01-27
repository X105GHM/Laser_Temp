#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <Arduino.h>

class BatterySensor
{
public:
    BatterySensor(uint8_t pin);
    float readBatteryVoltage();

private:
    uint8_t sensorPin;
    static constexpr float ADC_REF_VOLTAGE = 5.0;
    static constexpr int ADC_MAX_VALUE = 1023;
    static constexpr float VOLTAGE_DIVIDER_RATIO = 2.0;
};

#endif
