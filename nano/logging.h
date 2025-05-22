#ifndef LOG_H
#define LOG_H

#include <Arduino.h>
#include "config.h"

// Global variables
extern float gBatteryVolts;
extern int gStrategy;
extern int gADC_Strategy;
extern int gIR_Left, gIR_Right, gDistance1, gDistance2, gDistance3, gDIP_Switch;

class Logger;

extern Logger logger;

class Logger
{
public:
  void allData()
  {
    Serial.print(F("IR Left: "));
    Serial.print(gIR_Left);
    Serial.print(F("  IR Right: "));
    Serial.print(gIR_Right);
    Serial.print(F("  Distance 1: "));
    Serial.print(gDistance1);
    Serial.print(F("  Distance 2: "));
    Serial.print(gDistance2);
    Serial.print(F("  Distance 3: "));
    Serial.print(gDistance3);
    Serial.print(F("  Battery: "));
    Serial.print(gBatteryVolts);
    Serial.print(F("  Strategy: "));
    Serial.print(gStrategy);
    Serial.print(F("  Raw: "));
    Serial.println(gDIP_Switch);
  }

  void lineData()
  {
    Serial.print(F("IR Left: "));
    Serial.print(gIR_Left);
    Serial.print(F("  IR Right: "));
    Serial.println(gIR_Right);
  }

  void distanceData()
  {
    Serial.print(F("  Distance 1: "));
    Serial.print(gDistance1);
    Serial.print(F("  Distance 2: "));
    Serial.print(gDistance2);
    Serial.print(F("  Distance 3: "));
    Serial.println(gDistance3);
  }

  void batteryData()
  {
    Serial.print(F("  Battery: "));
    Serial.println(gBatteryVolts);
  }

  void strategyData()
  {
    Serial.print(F("  Strategy: "));
    Serial.print(gStrategy);
    Serial.print(F("  Raw: "));
    Serial.println(gDIP_Switch);
  }
};

#endif

// EOF
