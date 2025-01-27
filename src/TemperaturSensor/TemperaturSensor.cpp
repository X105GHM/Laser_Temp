#include "TemperaturSensor/TemperaturSensor.h"

TemperatureSensor::TemperatureSensor(uint8_t pin) : sensorPin(pin)
{
    pinMode(sensorPin, INPUT);
}

float TemperatureSensor::readTemperature()
{
    int adcValue = analogRead(sensorPin);
    float voltage = adcValue * (5.0 / 1023.0);
    float resistance = R_REF * ((5.0 / voltage) - 1.0);
    float tempKelvin = (BETA * T0) / (T0 * log(resistance / R0) + BETA);
    return tempKelvin - 273.15;
}
