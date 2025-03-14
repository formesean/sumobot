#ifndef TOF_SENSOR_HPP
#define TOF_SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

class ToFSensor
{
public:
  ToFSensor();
  bool begin();
  int readDistance();
  bool hasTimeout();

private:
  VL53L0X _sensor;
};

#endif

// EOF
