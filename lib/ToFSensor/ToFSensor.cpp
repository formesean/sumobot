#include "ToFSensor.hpp"

ToFSensor::ToFSensor(uint8_t shutdownPin) : _shutdownPin(shutdownPin) {}

bool ToFSensor::begin(uint8_t address)
{
  _address = address;

  pinMode(_shutdownPin, OUTPUT);
  digitalWrite(_shutdownPin, LOW);
  delay(10);
  digitalWrite(_shutdownPin, HIGH);
  delay(10);

  if (!_sensor.begin(_address))
  {
    Serial.print(F("Failed to initialize ToF sensor at address 0x"));
    Serial.println(_address, HEX);
    return false;
  }

  return true;
}

void ToFSensor::setAddress(uint8_t newAddress)
{
  _address = newAddress;
}

int ToFSensor::readDistance()
{
  _sensor.rangingTest(&_measure, false);
  if (_measure.RangeStatus != 4)
  {
    return _measure.RangeMilliMeter;
  }
  return -1; // Out of range
}

// EOF
