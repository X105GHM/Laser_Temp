#ifndef UTILS_H
#define UTILS_H

#include <avr/io.h>
#include <stdint.h>
#include <math.h>

constexpr bool my_isnan(float x) noexcept
{
    return x != x;
}

constexpr float roundf_ATtiny(float val) noexcept
{
    return (val >= 0.0f) ? static_cast<int>(val + 0.5f) : static_cast<int>(val - 0.5f);
}

uint16_t readADC(uint8_t channel);

#endif // UTILS_H
