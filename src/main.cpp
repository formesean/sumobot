#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// TB6612FNG
#define PWMA 32
#define AIN2 33
#define AIN1 25
#define STBY 26
#define BIN1 14
#define BIN2 27
#define PWMB 12
#define SPEED 1023

#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
#define PWM_FREQ 15000
#define PWM_RESOLUTION 10

// VL53L0X
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define SHT_LOX1 19
#define SHT_LOX2 18

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;

// TPR-105F
#define IR1 35
#define IR2 34

void setID();
void read_dual_sensors();

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(1);

  // VL53L0X Setup
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);

  setID();

  // TPR-105F Setup
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // TB6612FNG Setup
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  ledcSetup(PWM_CHANNEL_A, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_CHANNEL_B, PWM_FREQ, PWM_RESOLUTION);

  ledcAttachPin(PWMA, PWM_CHANNEL_A);
  ledcAttachPin(PWMB, PWM_CHANNEL_B);
}

void loop()
{
  // int ir1_val = analogRead(IR1);
  // int ir2_val = analogRead(IR2);

  // Serial.print("1: ");
  // Serial.print(ir1_val);
  // Serial.print("  2: ");
  // Serial.println(ir2_val);

  read_dual_sensors();

  if (measure1.RangeMilliMeter < 100 && measure2.RangeMilliMeter < 100)
  {
    digitalWrite(STBY, HIGH);

    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, SPEED);
    ledcWrite(PWM_CHANNEL_B, SPEED);
  }
  else if (measure1.RangeMilliMeter < 100)
  {
    digitalWrite(STBY, HIGH);

    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, 0);
    ledcWrite(PWM_CHANNEL_B, SPEED);
  }
  else if (measure2.RangeMilliMeter < 100)
  {
    digitalWrite(STBY, HIGH);

    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, SPEED);
    ledcWrite(PWM_CHANNEL_B, 0);
  }
  else
  {
    digitalWrite(STBY, LOW);
  }

  delay(250);
}

void setID()
{
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);

  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  if (!lox1.begin(LOX1_ADDRESS))
  {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }
  delay(10);

  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  if (!lox2.begin(LOX2_ADDRESS))
  {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }
}

void read_dual_sensors()
{

  lox1.rangingTest(&measure1, false);
  lox2.rangingTest(&measure2, false);

  Serial.print(F("1: "));
  if (measure1.RangeStatus != 4)
    Serial.print(measure1.RangeMilliMeter);
  else
    Serial.print(F("Out of range"));

  Serial.print(F(" "));

  Serial.print(F("2: "));
  if (measure2.RangeStatus != 4)
    Serial.print(measure2.RangeMilliMeter);
  else
    Serial.print(F("Out of range"));

  Serial.println();
}

/*
void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("\nI2C Scanner");
  Wire.begin();
}

void loop()
{
  byte error, address;
  int nDevices = 0;
  Serial.println("Scanning...");

  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found.");
  delay(2000);
}
*/
