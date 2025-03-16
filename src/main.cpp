#include "../lib/ToFSensor/ToFSensor.hpp"
#include "../lib/Motors/Motors.hpp"

// TB6612FNG Motor Drivers
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10
#define ENA 5
#define ENB 6
#define SPEED 128

Motors motors1(IN1, IN2, IN3, IN4, ENA, ENB);
Motors motors2(IN1, IN2, IN3, IN4, ENA, ENB);

// VL53L0X ToF Sensors
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31

#define SHT_LOX1 2
#define SHT_LOX2 3

ToFSensor sensor1(SHT_LOX1);
ToFSensor sensor2(SHT_LOX2);

/*===================================Motor Driver Test=====================================*/
/*void setup()
{
  motors1.begin();
  motors2.begin();
}

void loop()
{
  motors1.forward(SPEED);
  motors2.forward(SPEED);
  delay(5000);

  motors1.backward(SPEED);
  motors2.backward(SPEED);
  delay(5000);

  motors1.left(SPEED);
  motors2.left(SPEED);
  delay(5000);

  motors1.right(SPEED);
  motors2.right(SPEED);
  delay(5000);
}*/

/*===================================ToF Sensor Test=====================================*/
/*void setup()
{
  Serial.begin(9600);
  while (!Serial)
    delay(1);

  Serial.println(F("Initializing ToF Sensors..."));

  if (!sensor1.begin(LOX1_ADDRESS))
  {
    Serial.println(F("Failed to initialize Sensor 1"));
    while (1)
      ;
  }

  if (!sensor2.begin(LOX2_ADDRESS))
  {
    Serial.println(F("Failed to initialize Sensor 2"));
    while (1)
      ;
  }
}

void loop()
{
  int distance1 = sensor1.readDistance();
  int distance2 = sensor2.readDistance();

  Serial.print(F("1: "));
  Serial.print(distance1 == -1 ? F("Out of range") : String(distance1));

  Serial.print(F(" 2: "));
  Serial.println(distance2 == -1 ? F("Out of range") : String(distance2));

  delay(100);
}*/
