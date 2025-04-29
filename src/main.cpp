#include <Arduino.h>
#include <Wire.h>
#include <driver/i2s.h>
#include "Adafruit_VL53L0X.h"
#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"

// Control
#define IR_REC_PIN 23
#define BIT1 9
#define BIT0 13

int strat = 0;
int strat_dir = 0;
bool stratExecuted = false;
bool setStrat = false;

// TB6612FNG
#define PWMA 32
#define AIN2 33
#define AIN1 25
#define STBY 26
#define BIN1 14
#define BIN2 27
#define PWMB 12
#define SPEED 128
#define MAX_SPEED 255
#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
#define PWM_FREQ 16000
#define PWM_RESOLUTION 8

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

// Enums and Function Prototype

enum Direction
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

void strategy(int strat);
void setMotorPWM(int speedA, int speedB);
void setMotorPins(bool ain1, bool ain2, bool bin1, bool bin2);
void motors(int speed, Direction direction, int delay_ms);
void triggerStrategyAdjustment();

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(600000);

  // ADC1 Setup
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12);
  adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_12);

  // Control Setup
  pinMode(2, OUTPUT);
  pinMode(IR_REC_PIN, INPUT);

  pinMode(BIT0, INPUT_PULLUP);
  pinMode(BIT1, INPUT_PULLUP);

  // VL53L0X Setup
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);
  pinMode(SHT_LOX3, OUTPUT);
  pinMode(SHT_LOX4, OUTPUT);

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  digitalWrite(SHT_LOX4, LOW);
  delay(10);

  digitalWrite(SHT_LOX1, HIGH);
  lox1.begin(LOX1_ADDRESS);

  digitalWrite(SHT_LOX2, HIGH);
  lox2.begin(LOX2_ADDRESS);

  digitalWrite(SHT_LOX3, HIGH);
  lox3.begin(LOX3_ADDRESS);

  digitalWrite(SHT_LOX4, HIGH);
  lox4.begin(LOX4_ADDRESS);

  for (auto sensor : sensors)
    sensor->setMeasurementTimingBudgetMicroSeconds(25000);

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
  bool start_button = digitalRead(IR_REC_PIN);

  if (!setStrat)
  {
    digitalWrite(2, HIGH);

    strat = ((!digitalRead(BIT1)) << 1) | (!digitalRead(BIT0));
    // Serial.printf("strat: %d\n", strat);

    sensors[0]->rangingTest(&measures[0], false);
    sensors[3]->rangingTest(&measures[3], false);

    if (measures[0].RangeMilliMeter < 100)
    {
      strat_dir--;
      triggerStrategyAdjustment();
    }
    if (measures[3].RangeMilliMeter < 100)
    {
      strat_dir++;
      triggerStrategyAdjustment();
    }
  }

  while (start_button == LOW)
  {
    digitalWrite(2, HIGH);

    if (!stratExecuted)
    {
      strategy(strat);
      stratExecuted = true;
    }

    uint16_t ir1_raw = adc1_get_raw(ADC1_CHANNEL_6);
    uint16_t ir2_raw = adc1_get_raw(ADC1_CHANNEL_7);

    // Serial.printf("IR1: %d\t\t IR2: %d\n", ir1_raw, ir2_raw);

    for (uint8_t i = 0; i < 4; i++)
      sensors[i]->rangingTest(&measures[i], false);

    // Serial.printf("1: %dmm\t\t2: %dmm\t\t3: %dmm\t\t4: %dmm\n",
    //               measures[0].RangeMilliMeter,
    //               measures[1].RangeMilliMeter,
    //               measures[2].RangeMilliMeter,
    //               measures[3].RangeMilliMeter);

    // motors(0, FORWARD, 0);

    if (ir1_raw > 250 && ir2_raw > 250)
    {
      if (measures[1].RangeMilliMeter < 200 && measures[2].RangeMilliMeter < 200)
        motors(MAX_SPEED, FORWARD, 0);
      else if (measures[0].RangeMilliMeter < 650)
        motors(MAX_SPEED, LEFT, 0);
      else if (measures[3].RangeMilliMeter < 650)
        motors(MAX_SPEED, RIGHT, 0);
      else
        motors(70, FORWARD, 0);
    }
    else
    {
      motors(MAX_SPEED, BACKWARD, 350);
      motors(MAX_SPEED, LEFT, 300);
    }
  }
}

void strategy(int strat)
{
  switch (strat)
  {
  case 0:
    if (strat_dir > 0)
      motors(MAX_SPEED, FORWARD, 500);
    break;

  case 1:
    // palikod
    if (strat_dir < 0)
      motors(MAX_SPEED, LEFT, 380);
    if (strat_dir > 0)
      motors(MAX_SPEED, RIGHT, 380);
    break;

  case 2:
    // pakilid
    if (strat_dir < 0)
      motors(MAX_SPEED, LEFT, 150);
    if (strat_dir > 0)
      motors(MAX_SPEED, RIGHT, 150);
    break;

  case 3:
    // pacurve
    if (strat_dir < 0)
    {
      motors(MAX_SPEED, LEFT, 190);
      setMotorPWM(MAX_SPEED * .70, MAX_SPEED * .55);
      setMotorPins(HIGH, LOW, LOW, HIGH);
      delay(900);
      motors(MAX_SPEED, RIGHT, 230);
    }
    if (strat_dir > 0)
    {
      motors(MAX_SPEED, RIGHT, 190);
      setMotorPWM(MAX_SPEED * .50, MAX_SPEED * .70);
      setMotorPins(HIGH, LOW, LOW, HIGH);
      delay(900);
      motors(MAX_SPEED, LEFT, 230);
    }
    break;
  }
}

void setMotorPWM(int speedA, int speedB)
{
  ledcWrite(PWM_CHANNEL_A, speedA);
  ledcWrite(PWM_CHANNEL_B, speedB);
}

void setMotorPins(bool ain2, bool ain1, bool bin1, bool bin2)
{
  digitalWrite(AIN2, ain2);
  digitalWrite(AIN1, ain1);
  digitalWrite(BIN1, bin1);
  digitalWrite(BIN2, bin2);
}

void motors(int speed, Direction direction, int delay_ms)
{
  switch (direction)
  {
  case FORWARD:
    setMotorPWM(speed, speed);
    setMotorPins(HIGH, LOW, LOW, HIGH);
    break;

  case BACKWARD:
    setMotorPWM(speed, speed);
    setMotorPins(LOW, HIGH, HIGH, LOW);
    break;

  case LEFT:
    setMotorPWM(speed, speed * 0.50);
    setMotorPins(LOW, HIGH, LOW, HIGH);
    break;

  case RIGHT:
    setMotorPWM(speed * 0.50, speed);
    setMotorPins(HIGH, LOW, HIGH, LOW);
    break;
  }

  delay(delay_ms);
}

void triggerStrategyAdjustment()
{
  setStrat = true;
  digitalWrite(2, LOW);
  delay(150);
}

// EOF
