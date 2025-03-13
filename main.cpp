#include <stdio.h>
#include "pico/stdlib.h"
#include "ir-sensor.hpp"

#define NUM_SENSORS 5

int main()
{
  stdio_init_all();

  int sensorPins[NUM_SENSORS] = {1, 2, 4, 5, 6};
  IRSensor irSensor(sensorPins, NUM_SENSORS);
  irSensor.init();

  int sensorValues[NUM_SENSORS];

  while (true)
  {
    irSensor.readSensors(sensorValues);

    printf("Sensor Readings: ");
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      printf("%d ", sensorValues[i]);
    }
    printf("\n");

    sleep_ms(500);
  }

  return 0;
}
