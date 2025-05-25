#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "adc.h"
#include "config.h"

class Sensors;

extern Sensors sensors;

class Sensors
{
public:
  void begin_distance()
  {
    pinMode(DIST_LEFT, INPUT);
    pinMode(DIST_MIDDLE, INPUT);
    pinMode(DIST_RIGHT, INPUT);
  }

  void begin_line()
  {
    pinMode(LINE_LEFT, INPUT);
    pinMode(LINE_RIGHT, INPUT);
    pinMode(EMITTER_LEFT, OUTPUT);
    pinMode(EMITTER_RIGHT, OUTPUT);
  }

  void line_both_emitter_on()
  {
    digitalWrite(EMITTER_LEFT, HIGH);
    digitalWrite(EMITTER_RIGHT, HIGH);
  }

  void line_both_emitter_off()
  {
    digitalWrite(EMITTER_LEFT, LOW);
    digitalWrite(EMITTER_RIGHT, LOW);
  }

  void line_left_emitter_on()
  {
    digitalWrite(EMITTER_LEFT, HIGH);
  }

  void line_left_emitter_off()
  {
    digitalWrite(EMITTER_LEFT, HIGH);
  }

  void line_right_emitter_on()
  {
    digitalWrite(EMITTER_RIGHT, HIGH);
  }

  void line_right_emitter_off()
  {
    digitalWrite(EMITTER_RIGHT, LOW);
  }

  void read_all()
  {
    line_both_emitter_off();
    line_left_emitter_on();
    delayMicroseconds(100);
    m_ir_left = adc.fast_read(LINE_LEFT);
    line_right_emitter_on();
    delayMicroseconds(100);
    m_ir_right = adc.fast_read(LINE_RIGHT);
    line_both_emitter_off();

    m_dist1 = adc.fast_read(DIST_LEFT);
    m_dist2 = adc.fast_read(DIST_MIDDLE);
    m_dist3 = adc.fast_read(DIST_RIGHT);

    m_dip_raw = adc.fast_read(DIP_SW);

    int raw_batt = adc.fast_read(BATTERY_VOLTS);
    m_battery_volts = raw_batt * (5.0f * BATTERY_DIVIDER_RATIO / 1023.0f);

    m_strategy_adc = m_dip_raw;
    m_strategy = decode_strategy(m_strategy_adc);

    // Update global variables
    gIR_Left = m_ir_left;
    gIR_Right = m_ir_right;
    gDistance1 = m_dist1;
    gDistance2 = m_dist2;
    gDistance3 = m_dist3;
    gDIP_Switch = m_dip_raw;
    gBatteryVolts = m_battery_volts;
    gADC_Strategy = m_strategy_adc;
    gStrategy = m_strategy;
  }

private:
  int decode_strategy(int value) const
  {
    if (value >= 1000)
      return 0;
    if (value >= 800)
      return 2;
    if (value >= 500)
      return 1;
    if (value >= 400)
      return 3;
    return -1;
  }

  float m_battery_volts = 0;
  int m_strategy_adc = 0;
  int m_strategy = -1;

  int m_ir_left = 0;
  int m_ir_right = 0;
  int m_dist1 = 0;
  int m_dist2 = 0;
  int m_dist3 = 0;
  int m_dip_raw = 0;
};

#endif

// EOF
