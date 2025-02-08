#include "millis.h"

volatile uint32_t g_millis = 0;

ISR(TIMER1_COMPA_vect)
{
    g_millis++;
}
