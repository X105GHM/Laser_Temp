#include <Arduino.h>
#include <TM1637Display.h>
#include "TemperaturSensor/TemperaturSensor.h"
#include "BatterieSensor/BatterieSensor.h"
#include "FanController/FanController.h"

constexpr uint8_t TM1637_CLK = PB2;
constexpr uint8_t TM1637_DIO = PB1;
constexpr uint8_t MOSFET_PWM = PB0;
constexpr uint8_t PTC_SENSOR = PB3;
constexpr uint8_t BATTERY_SENSOR = PB4;

TM1637Display display(TM1637_CLK, TM1637_DIO);
TemperatureSensor tempSensor(PTC_SENSOR);
BatterySensor batterySensor(BATTERY_SENSOR);
FanController fanController(MOSFET_PWM);

unsigned long lastUpdate = 0;
unsigned long lastDisplaySwitch = 0;
constexpr unsigned long updateInterval = 1000;
constexpr unsigned long displaySwitchInterval = 5000;
bool showTemperature = true;

void setup()
{
  display.setBrightness(7);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= updateInterval)
  {
    lastUpdate = currentMillis;
    float temperature = tempSensor.readTemperature();
    float batteryVoltage = batterySensor.readBatteryVoltage();
    fanController.updatePWMWithHysteresis(temperature);

    if (currentMillis - lastDisplaySwitch >= displaySwitchInterval)
    {
      lastDisplaySwitch = currentMillis;
      showTemperature = !showTemperature;
    }

    if (showTemperature)
    {
      display.showNumberDecEx(int(temperature * 10), 0x80, false);
    }
    else
    {
      display.showNumberDec(int(batteryVoltage * 10), false);
    }
  }
}
