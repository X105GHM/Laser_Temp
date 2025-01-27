#include "BatterieSensor/BatterieSensor.h"

BatterySensor::BatterySensor(uint8_t pin) : sensorPin(pin)
{
    pinMode(sensorPin, INPUT);
}

float BatterySensor::readBatteryVoltage()
{
    int adcValue = analogRead(sensorPin);
    float voltage = (adcValue * (ADC_REF_VOLTAGE / ADC_MAX_VALUE)) * VOLTAGE_DIVIDER_RATIO;
    return voltage;
}
