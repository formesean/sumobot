#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// Control
#define BOOT_BUTTON_PIN 0
#define BIT2 13
#define BIT1 9
#define BIT0 10

int strat = 0;
bool stratExecuted = false;
bool delayDone = false;

// TB6612FNG
#define PWMA 32
#define AIN2 33
#define AIN1 25
#define STBY 26
#define BIN1 14
#define BIN2 27
#define PWMB 12
#define SPEED 400
#define MAX_SPEED 1023
#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
#define PWM_FREQ 15000
#define PWM_RESOLUTION 10

bool speedRampedUp = false;

// VL53L0X
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32
#define LOX4_ADDRESS 0x33
#define SHT_LOX1 19
#define SHT_LOX2 18
#define SHT_LOX3 17
#define SHT_LOX4 16

Adafruit_VL53L0X lox1, lox2, lox3, lox4;

VL53L0X_RangingMeasurementData_t measures[4];
Adafruit_VL53L0X *sensors[] = {&lox1, &lox2, &lox3, &lox4};

// TPR-105F
#define IR1 35
#define IR2 34

int ir1_val = 0;
int ir2_val = 0;

void strategy(int strat);

void setup()
{
  // Control Setup
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(2, OUTPUT);

  pinMode(BIT0, INPUT_PULLUP);
  pinMode(BIT1, INPUT_PULLUP);
  pinMode(BIT2, INPUT_PULLUP);

  int bit0 = !digitalRead(BIT0);
  int bit1 = !digitalRead(BIT1);
  int bit2 = !digitalRead(BIT2);
  strat = (bit2 << 2) | (bit1 << 1) | bit0;

  // VL53L0X Setup
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);

  digitalWrite(SHT_LOX1, HIGH);
  lox1.begin(LOX1_ADDRESS);

  digitalWrite(SHT_LOX2, HIGH);
  lox2.begin(LOX2_ADDRESS);

  digitalWrite(SHT_LOX3, HIGH);
  lox3.begin(LOX3_ADDRESS);

  digitalWrite(SHT_LOX4, HIGH);
  lox4.begin(LOX4_ADDRESS);

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

  digitalWrite(STBY, HIGH);
}

void loop()
{
  bool start_button = digitalRead(BOOT_BUTTON_PIN);

  while (start_button == LOW)
  {
    if (!delayDone)
    {
      delay(5000);
      digitalWrite(2, HIGH);
      delayDone = true;
    }

    for (uint8_t i = 0; i < 4; i++)
      sensors[i]->rangingTest(&measures[i], false);

    ir1_val = analogRead(IR1);
    ir2_val = analogRead(IR2);

    ledcWrite(PWM_CHANNEL_A, SPEED);
    ledcWrite(PWM_CHANNEL_B, SPEED);

    if (!stratExecuted)
    {
      strategy(strat);
      stratExecuted = true;
    }

    if (ir1_val < 4090 || ir2_val < 4090)
    {
      if (measures[0].RangeMilliMeter < 500 && measures[1].RangeMilliMeter < 500)
      {
        if (!speedRampedUp)
        {
          for (int speed = 0; speed <= 800; speed += 50)
          {
            ledcWrite(PWM_CHANNEL_A, speed);
            ledcWrite(PWM_CHANNEL_B, speed);
            delay(10);
          }
          speedRampedUp = true;
        }

        ledcWrite(PWM_CHANNEL_A, MAX_SPEED);
        ledcWrite(PWM_CHANNEL_B, MAX_SPEED);

        digitalWrite(AIN2, HIGH);
        digitalWrite(AIN1, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
      }
      else if (measures[0].RangeMilliMeter < 500 || measures[2].RangeMilliMeter < 500)
      {
        digitalWrite(AIN2, LOW);
        digitalWrite(AIN1, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
      }
      else if (measures[1].RangeMilliMeter < 500 || measures[3].RangeMilliMeter < 500)
      {
        digitalWrite(AIN2, HIGH);
        digitalWrite(AIN1, LOW);

        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
      }
      else
      {
        digitalWrite(AIN2, HIGH);
        digitalWrite(AIN1, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
        ledcWrite(PWM_CHANNEL_A, SPEED * .50);
        ledcWrite(PWM_CHANNEL_B, SPEED * .50);
      }
    }
    else
    {
      digitalWrite(AIN2, LOW);
      digitalWrite(AIN1, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      delay(300);

      digitalWrite(AIN2, HIGH);
      digitalWrite(AIN1, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      delay(200);
    }
  }
}

void strategy(int strat)
{
  switch (strat)
  {
  case 0:
    break;

  case 1:
    // Hesi
    digitalWrite(AIN2, LOW);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(200);
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    ledcWrite(PWM_CHANNEL_A, MAX_SPEED * .65);
    ledcWrite(PWM_CHANNEL_B, MAX_SPEED * .65);
    delay(300);
    break;

  case 2:
    // Woodpecker
    for (int i = 0; i < 2; i++)
    {
      ledcWrite(PWM_CHANNEL_A, 700);
      ledcWrite(PWM_CHANNEL_B, 700);
      digitalWrite(STBY, HIGH);
      digitalWrite(AIN2, HIGH);
      digitalWrite(AIN1, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      delay(70);
      ledcWrite(PWM_CHANNEL_A, 0);
      ledcWrite(PWM_CHANNEL_B, 0);
      delay(400);
    }
    ledcWrite(PWM_CHANNEL_A, SPEED);
    ledcWrite(PWM_CHANNEL_B, SPEED);
    digitalWrite(STBY, HIGH);
    break;

  case 3:
    // Bait and Switch
    ledcWrite(PWM_CHANNEL_A, 700);
    ledcWrite(PWM_CHANNEL_B, 700);
    digitalWrite(AIN2, LOW);
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    delay(70);
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    delay(200);
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    delay(250);
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    delay(300);
    ledcWrite(PWM_CHANNEL_A, SPEED);
    ledcWrite(PWM_CHANNEL_B, SPEED);
    break;

  case 4:
    // Reverse Bait and Switch
    break;

  case 5:
    // Catapult
    break;

  default:
    break;
  }
}

// EOF
