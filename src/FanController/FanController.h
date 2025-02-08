#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class FanController
{
public:
    explicit FanController(uint8_t pin) noexcept;

    void updatePWMWithHysteresis(float temperature) noexcept;

private:
    uint8_t pwmPin;
    float lastTemperature;
    bool pwmDisabled;

    static constexpr uint8_t PWM_MIN = 20;
    static constexpr uint8_t PWM_MAX = 255; 
    static constexpr float TEMP_MIN = 27.0f; 
    static constexpr float TEMP_MAX = 40.0f; 
    static constexpr float HYSTERESIS = 1.5f;
};

inline void initTimer0PWM() noexcept
{
    TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS01) | (1 << CS00);
    OCR0A = 0;
}

#endif // FAN_CONTROLLER_H