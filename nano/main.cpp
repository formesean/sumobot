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

bool delayDone = false;
float gBatteryVolts;
int gStrategy, gADC_Strategy, gIR_Left, gIR_Right, gDistance1, gDistance2, gDistance3, gDIP_Switch;
volatile bool doSensorRead = false;

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

  sensors.line_emitter_on();
}

void loop()
{
  bool start = digitalRead(START_SW);

  while (start == 0)
  {
    if (!delayDone)
    {
      delayDone = true;
      delay(5000);
      digitalWrite(LED_BUILTIN, 1);
    }

    if (doSensorRead)
    {
      doSensorRead = false;
      sensors.read_all();
    }

    // logger.batteryData();
    // logger.strategyData();
    // logger.lineData();
    // logger.distanceData();
    // logger.allData();

    if (gDistance2 > 300)
      motors.motorAction(Motors::FORWARD_100);
    else if (gDistance1 > 300)
      motors.motorAction(Motors::SPIN_LEFT_25);
    else if (gDistance3 > 300)
      motors.motorAction(Motors::SPIN_RIGHT_25);
    else
      motors.motorAction(Motors::FORWARD_10);
  }
}

// EOF
