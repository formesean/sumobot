#include "Motors.hpp"

Motors::Motors(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t ena, uint8_t enb)
    : _in1(in1), _in2(in2), _in3(in3), _in4(in4), _ena(ena), _enb(enb) {}

void Motors::begin()
{
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_in3, OUTPUT);
  pinMode(_in4, OUTPUT);
  pinMode(_ena, OUTPUT);
  pinMode(_enb, OUTPUT);
}

void Motors::forward(uint8_t speed)
{
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);
  digitalWrite(_in3, LOW);
  digitalWrite(_in4, HIGH);
  analogWrite(_ena, speed);
  analogWrite(_enb, speed);
}

void Motors::backward(uint8_t speed)
{
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);
  digitalWrite(_in3, HIGH);
  digitalWrite(_in4, LOW);
  analogWrite(_ena, speed);
  analogWrite(_enb, speed);
}

void Motors::left(uint8_t speed)
{
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, LOW);
  digitalWrite(_in3, HIGH);
  digitalWrite(_in4, LOW);
  analogWrite(_ena, speed);
  analogWrite(_enb, speed);
}

void Motors::right(uint8_t speed)
{
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, HIGH);
  digitalWrite(_in3, LOW);
  digitalWrite(_in4, HIGH);
  analogWrite(_ena, speed);
  analogWrite(_enb, speed);
}

void Motors::stop()
{
  analogWrite(_ena, 0);
  analogWrite(_enb, 0);
}

// EOF
