#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <TM1637TinyDisplay.h>
#include "HelpFunctions/millis.h"
#include "HelpFunctions/utils.h"
#include "BatterieSensor/BatterieSensor.h"
#include "TemperaturSensor/TemperaturSensor.h"
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

volatile bool showTemperature = true;
volatile bool blinkState = false;

int main(void)
{
  initTimer1();
  initTimer0PWM();

  ADMUX = 0;
  ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);

  displayController.setBrightness(7);
  displayController.updateDisplay(0.0f, 0.0f, true);

  _delay_ms(500);

  uint32_t lastUpdate = millis();
  uint32_t lastBlinkUpdate = millis();
  uint32_t lastDisplayToggle = millis();

  constexpr uint32_t updateInterval = 500;
  constexpr uint32_t blinkInterval = 180;           
  constexpr uint32_t displayToggleInterval = 10000;

  constexpr float voltageThresholdHigh = 25.2f;
  constexpr float voltageThresholdLow = 20.0f;

  sei();

  while (true)
  {
    const uint32_t currentMillis = millis();

    if (currentMillis - lastDisplayToggle >= displayToggleInterval)
    {
      lastDisplayToggle = currentMillis;
      showTemperature = !showTemperature;
    }

    const float batteryVoltage = batterySensor.readBatteryVoltage();
    const float temperature = tempSensor.readTemperature();

    if (currentMillis - lastUpdate >= updateInterval)
    {
      lastUpdate = currentMillis;
      if (showTemperature)
      {
        displayController.setBrightness(1);
      }
      else
      {
        displayController.setBrightness(7);
      }
      displayController.updateDisplay(temperature, batteryVoltage, showTemperature);
    }

    if (!showTemperature && (batteryVoltage > voltageThresholdHigh || batteryVoltage < voltageThresholdLow))
    {
      if (currentMillis - lastBlinkUpdate >= blinkInterval)
      {
        lastBlinkUpdate = currentMillis;
        blinkState = !blinkState;
        displayController.setBrightness(blinkState ? 0 : 7);
      }
    }
    else if (!showTemperature)
    {
      displayController.setBrightness(7);
    }
    fanController.updatePWMWithHysteresis(temperature);
  }

  return 0;
}