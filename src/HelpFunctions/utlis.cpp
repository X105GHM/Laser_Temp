#include "utils.h"
#include <util/delay.h>

uint16_t readADC(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    _delay_us(100);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
        ;

    uint8_t low = ADCL;
    uint8_t high = ADCH;
    return (static_cast<uint16_t>(high) << 8) | low;
}
