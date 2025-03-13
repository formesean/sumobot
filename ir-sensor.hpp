#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "hardware/gpio.h"

class IRSensor
{
public:
  IRSensor(int pins[], int numSensors);
  void init();
  void readSensors(int sensorValues[]);

private:
  int *sensorPins;
  int numSensors;
};

#endif // IRSENSOR_H
