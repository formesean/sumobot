#ifndef ADC_H
#define ADC_H

#include <Arduino.h>
#include <wiring_private.h>
#include "config.h"

// Global variables
extern float gBatteryVolts;
extern int gStrategy;
extern int gADC_Strategy;
extern int gIR_Left, gIR_Right, gDistance1, gDistance2, gDistance3, gDIP_Switch;

class ADCManager;

extern ADCManager adc;

class ADCManager
{
public:
  void begin()
  {
    // Set ADC prescaler to 32
    bitSet(ADCSRA, ADPS2);
    bitClear(ADCSRA, ADPS1);
    bitSet(ADCSRA, ADPS0);
  }

  int fast_read(byte ADCpin)
  {
    byte ADCSRAoriginal = ADCSRA;
    ADCSRA = (ADCSRA & B11111000) | B101;
    int adc = analogRead(ADCpin); // Dummy read
    adc = analogRead(ADCpin);
    ADCSRA = ADCSRAoriginal;
    return adc;
  }
};

#endif

// EOF
