#include "ir-sensor.hpp"

IRSensor::IRSensor(int pins[], int numSensors)
{
  this->sensorPins = pins;
  this->numSensors = numSensors;
}

void IRSensor::init()
{
  for (int i = 0; i < numSensors; i++)
  {
    gpio_init(sensorPins[i]);
    gpio_set_dir(sensorPins[i], GPIO_IN);
  }
}

void IRSensor::readSensors(int sensorValues[])
{
  for (int i = 0; i < numSensors; i++)
  {
    sensorValues[i] = gpio_get(sensorPins[i]);
  }
}
