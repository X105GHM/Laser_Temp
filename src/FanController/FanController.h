#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include <stdint.h>
#include <avr/io.h>
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

static inline uint8_t mapValue(float x, float in_min, float in_max, uint8_t out_min, uint8_t out_max)
{
    if (fabs(in_max - in_min) < 1e-6)
    {
        return out_min;
    }
    if (x <= in_min)
        return out_min;
    if (x >= in_max)
        return out_max;
    return static_cast<uint8_t>((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

#endif // FAN_CONTROLLER_H