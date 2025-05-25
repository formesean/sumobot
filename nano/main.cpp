#include <Arduino.h>
#include "config.h"
#include "systick.h"
#include "adc.h"
#include "motors.h"
#include "sensors.h"
#include "logging.h"

// Global objects & variables
Systick systick;
ADCManager adc;
Motors motors;
Sensors sensors;
Logger logger;

volatile bool doSensorRead = false;
bool delayDone = false;
bool stratSelected = false;
bool prevDistance2High = false;
bool prevDistance3High = false;
float gBatteryVolts;
int selectStrat = 0;
int gStrategy, gADC_Strategy, gIR_Left, gIR_Right, gDistance1, gDistance2, gDistance3, gDIP_Switch;

void strategy(int choice);

ISR(TIMER2_COMPA_vect, ISR_NOBLOCK)
{
  doSensorRead = true;
}

void setup()
{
  Serial.begin(SERIAL_BAUDRATE);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(START_SW, INPUT_PULLUP);

  digitalWrite(LED_BUILTIN, 0);
  pinMode(DIP_SW, INPUT);
  pinMode(BATTERY_VOLTS, INPUT);

  adc.begin();
  motors.begin();
  sensors.begin_distance();
  sensors.begin_line();
  systick.begin();
}

void loop()
{
  bool start = digitalRead(START_SW);

  if (doSensorRead)
  {
    doSensorRead = false;
    sensors.read_all();

    // Rising edge detection for Distance2
    bool isDistance2High = gDistance2 > 300;
    bool isDistance3High = gDistance3 > 300;

    if (!stratSelected)
    {
      if (isDistance2High && !prevDistance2High)
      {
        selectStrat++;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
      }

      if (isDistance3High && !prevDistance3High)
      {
        stratSelected = true;
        digitalWrite(LED_BUILTIN, HIGH);
      }
    }

    // Save current state for next loop
    prevDistance2High = isDistance2High;
    prevDistance3High = isDistance3High;
  }

  while (start == 0)
  {
    if (doSensorRead)
    {
      doSensorRead = false;
      sensors.read_all();
    }

    // logger.lineData();

    if (!delayDone)
    {
      delayDone = true;
      // delay(5000);
      strategy(selectStrat);
    }

    if (gIR_Left > 70 && gIR_Right > 20)
    {
      motors.motorAction(Motors::REVERSE_75);
      delay(250);
      motors.motorAction(Motors::SPIN_LEFT_50);
      delay(400);
    }
    else
    {
      if (gDistance2 > 200)
        motors.motorAction(Motors::FORWARD_100);
      else if (gDistance1 > 200)
        motors.motorAction(Motors::SPIN_LEFT_50);
      else if (gDistance3 > 200)
        motors.motorAction(Motors::SPIN_RIGHT_50);
      else
        motors.motorAction(Motors::FORWARD_25);
    }
  }
}

void strategy(int choice)
{
  switch (choice)
  {
  case 1:
    motors.motorAction(Motors::REVERSE_75);
    delay(250);
    motors.motorAction(Motors::SPIN_LEFT_50);
    delay(400);
    break;

  case 2:
    motors.motorAction(Motors::REVERSE_75);
    delay(250);
    motors.motorAction(Motors::SPIN_RIGHT_50);
    delay(400);
    break;

  case 3:
    motors.motorAction(Motors::REVERSE_75);
    delay(100);
    motors.motorAction(Motors::SPIN_LEFT_50);
    delay(200);
    motors.motorAction(Motors::BIG_CURVE_LEFT);
    delay(750);
    motors.motorAction(Motors::SPIN_LEFT_50);
    delay(350);
    break;

  case 4:
    motors.motorAction(Motors::REVERSE_75);
    delay(100);
    motors.motorAction(Motors::SPIN_RIGHT_50);
    delay(200);
    motors.motorAction(Motors::BIG_CURVE_RIGHT);
    delay(750);
    motors.motorAction(Motors::SPIN_RIGHT_50);
    delay(350);
    break;
  }
}

// EOF
