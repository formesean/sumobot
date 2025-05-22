#ifndef SYSTICK_H
#define SYSTICK_H

#include <Arduino.h>
#include "config.h"

class Systick;

extern Systick systick;

class Systick
{
public:
  void begin()
  {
    bitClear(TCCR2B, WGM22); // set the mode for timer 2
    bitClear(TCCR2A, WGM20);
    bitSet(TCCR2A, WGM21);
    bitSet(TCCR2B, CS22); // set divisor to 128 => timer clock = 125kHz
    bitClear(TCCR2B, CS21);
    bitSet(TCCR2B, CS20);
    OCR2A = 249;            // set the timer frequency
    bitSet(TIMSK2, OCIE2A); // enable the timer interrupt
    delay(40);
  }
};

#endif

// EOF
