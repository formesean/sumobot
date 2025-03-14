#ifndef MOTORS_HPP
#define MOTORS_HPP

#include <Arduino.h>

class Motors
{
public:
  Motors(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t ena, uint8_t enb);
  void begin();
  void forward(uint8_t speed);
  void backward(uint8_t speed);
  void left(uint8_t speed);
  void right(uint8_t speed);
  void stop();

private:
  uint8_t _in1, _in2, _in3, _in4, _ena, _enb;
};

#endif

// EOF
