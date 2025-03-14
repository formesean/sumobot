#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class LED
{
public:
  LED(uint8_t pin = LED_BUILTIN);
  void begin();
  void on();
  void off();
  void toggle();
  void blink(unsigned long onTime, unsigned long offTime);
  void update();

private:
  uint8_t _pin;
  bool _state;
  unsigned long _lastToggle;
  unsigned long _onTime;
  unsigned long _offTime;
  bool _isBlinking;
};

#endif

// EOF
