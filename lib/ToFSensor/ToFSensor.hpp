#ifndef TOF_SENSOR_HPP
#define TOF_SENSOR_HPP

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

class ToFSensor
{
public:
  ToFSensor(uint8_t shutdownPin);
  bool begin(uint8_t address);
  void setAddress(uint8_t newAddress);
  int readDistance();

private:
  Adafruit_VL53L0X _sensor;
  VL53L0X_RangingMeasurementData_t _measure;
  uint8_t _shutdownPin;
  uint8_t _address;
};

#endif

// EOF
