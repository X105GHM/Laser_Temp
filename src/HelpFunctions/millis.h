#ifndef MILLIS_H
#define MILLIS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern volatile uint32_t g_millis;

inline uint32_t millis()
{
    uint32_t m;
    uint8_t sreg = SREG;
    cli();
    m = g_millis;
    SREG = sreg;
    return m;
}

inline void initTimer1()
{
    TCCR1 = (1 << CTC1) | (1 << CS12);
    OCR1A = 124;
    TIMSK |= (1 << OCIE1A);
}

#endif // MILLIS_H
