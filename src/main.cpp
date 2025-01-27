#include <Arduino.h>
#include <TM1637Display.h>
#include "TemperaturSensor/TemperaturSensor.h"
#include "BatterieSensor/BatterieSensor.h"
#include "FanController/FanController.h"
#include "DisplayController/DisplayController.h"

constexpr uint8_t TM1637_CLK = PB2;
constexpr uint8_t TM1637_DIO = PB1;
constexpr uint8_t MOSFET_PWM = PB0;
constexpr uint8_t NTC_SENSOR = PB3;
constexpr uint8_t BATTERY_SENSOR = PB4;

DisplayController displayController(TM1637_CLK, TM1637_DIO);
TemperatureSensor tempSensor(NTC_SENSOR);
BatterySensor batterySensor(BATTERY_SENSOR);
FanController fanController(MOSFET_PWM);

unsigned long lastUpdate = 0;
unsigned long lastActivity = 0;
constexpr unsigned long updateInterval = 1000;
constexpr unsigned long inactivityThreshold = 30000;
constexpr unsigned long blinkInterval = 180;
float lastTemperature = 0;
float lastBatteryVoltage = 0;
bool blinkState = false;
constexpr float voltageThresholdLow = 22.0;
constexpr float voltageThresholdHigh = 25.2;

void setup()
{
  displayController.setBrightness(7);
}

void loop()
{
  unsigned long currentMillis = millis();
  float batteryVoltage = batterySensor.readBatteryVoltage();
  float temperature = tempSensor.readTemperature();
  fanController.updatePWMWithHysteresis(temperature);

  if (currentMillis - lastUpdate >= updateInterval)
  {
    lastUpdate = currentMillis;
    displayController.updateDisplay(temperature, batteryVoltage);

    if (abs(temperature - lastTemperature) > 0.5 || abs(batteryVoltage - lastBatteryVoltage) > 0.1)
    {
      lastActivity = currentMillis;
    }
    lastTemperature = temperature;
    lastBatteryVoltage = batteryVoltage;
  }

  if (batteryVoltage < voltageThresholdLow || batteryVoltage > voltageThresholdHigh)
  {
    displayController.blinkDisplay(currentMillis, blinkInterval, blinkState);
  }
  else if (currentMillis - lastActivity > inactivityThreshold)
  {
    displayController.setBrightness(1);
  }
  else
  {
    displayController.setBrightness(7);
  }
}
