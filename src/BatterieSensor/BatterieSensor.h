#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <stdint.h>

class BatterySensor
{
public:
    
    explicit BatterySensor(uint8_t pin) noexcept;
    
    float readBatteryVoltage() noexcept;

private:

    uint8_t sensorPin;
    static constexpr float ADC_REF_VOLTAGE = 5.0f;
    static constexpr int   ADC_MAX_VALUE   = 1023;
    static constexpr float R1              = 1000000.0f; // 1 MΩ
    static constexpr float R2              = 100000.0f;  // 100 kΩ
    static constexpr float VOLTAGE_DIVIDER_RATIO = (R1 + R2) / R2;
};

#endif // BATTERY_SENSOR_H
