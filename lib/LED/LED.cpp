#include "LED.hpp"

LED::LED(uint8_t pin) : _pin(pin), _state(false), _lastToggle(0), _isBlinking(false) {}

void LED::begin()
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void LED::on()
{
  _isBlinking = false;
  _state = true;
  digitalWrite(_pin, HIGH);
}

void LED::off()
{
  _isBlinking = false;
  _state = false;
  digitalWrite(_pin, LOW);
}

void LED::toggle()
{
  _state = !_state;
  digitalWrite(_pin, _state ? HIGH : LOW);
}

void LED::blink(unsigned long onTime, unsigned long offTime)
{
  _isBlinking = true;
  _onTime = onTime;
  _offTime = offTime;
  _lastToggle = millis();
}

void LED::update()
{
  if (!_isBlinking)
    return;

  unsigned long currentTime = millis();
  unsigned long interval = _state ? _onTime : _offTime;

  if (currentTime - _lastToggle >= interval)
  {
    toggle();
    _lastToggle = currentTime;
  }
}

// EOF
