#include <Arduino.h>
#include <TM1637Display.h>
#include "TemperaturSensor/TemperaturSensor.h"
#include "FanController/FanController.h"

constexpr uint8_t TM1637_CLK = PB2;
constexpr uint8_t TM1637_DIO = PB1;
constexpr uint8_t MOSFET_PWM = PB0;
constexpr uint8_t PTC_SENSOR = PB3;

TM1637Display display(TM1637_CLK, TM1637_DIO);
TemperatureSensor tempSensor(PTC_SENSOR);
FanController fanController(MOSFET_PWM);

unsigned long lastUpdate = 0;
constexpr unsigned long updateInterval = 500;

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
    fanController.updatePWMWithHysteresis(temperature);
    display.showNumberDec(int(temperature), false);
  }
}