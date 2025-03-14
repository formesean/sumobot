#include "ToFSensor.hpp"

ToFSensor::ToFSensor() {}

bool ToFSensor::begin()
{
  Wire.begin();
  if (!_sensor.init())
  {
    return false;
  }
  _sensor.setTimeout(500);
  _sensor.startContinuous();
  return true;
}

int ToFSensor::readDistance()
{
  return _sensor.readRangeContinuousMillimeters();
}

bool ToFSensor::hasTimeout()
{
  return _sensor.timeoutOccurred();
}

// EOF
