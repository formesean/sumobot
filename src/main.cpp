#include <Arduino.h>
#include "../lib/Motors/Motors.hpp"
#include "../lib/ToFSensor/ToFSensor.hpp"
#include "../lib/LED/LED.hpp"

// Motors Pin Config
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENA 5
#define ENB 6

#define SPEED 150

Motors motors(IN1, IN2, IN3, IN4, ENA, ENB);
ToFSensor tof;

void setup()
{
  Serial.begin(9600);

  motors.begin();

  if (!tof.begin())
  {
    Serial.println("Failed");
  }
}

void loop()
{
  // motors.forward(SPEED);
  // delay(1000);
  // motors.backward(SPEED);
  // delay(1000);
  // motors.left(SPEED);
  // delay(1000);
  // motors.right(SPEED);
  // delay(1000);
  int distance = tof.readDistance();

  if (tof.hasTimeout())
    Serial.println("VL53L0X timeout!");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" mm");
  delay(100);
}
