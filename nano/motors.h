#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include "config.h"

// Global variables
extern float gBatteryVolts;

class Motors;

extern Motors motors;

class Motors
{
public:
  // Motor control constants for motorAction cases
  enum MotorAction
  {
    MOTORS_OFF,
    FORWARD_10,
    FORWARD_25,
    FORWARD_50,
    FORWARD_75,
    FORWARD_100,
    REVERSE_10,
    REVERSE_25,
    REVERSE_50,
    REVERSE_75,
    REVERSE_100,
    SPIN_LEFT_25,
    SPIN_LEFT_50,
    SPIN_RIGHT_25,
    SPIN_RIGHT_50,
    PIVOT_LEFT_25,
    PIVOT_RIGHT_25,
    CURVE_LEFT,
    CURVE_RIGHT,
    BIG_CURVE_LEFT,
    BIG_CURVE_RIGHT
  };

  void begin()
  {
    pinMode(MOTOR_LEFT_DIR, OUTPUT);
    pinMode(MOTOR_RIGHT_DIR, OUTPUT);
    pinMode(MOTOR_LEFT_PWM, OUTPUT);
    pinMode(MOTOR_RIGHT_PWM, OUTPUT);

    analogWrite(MOTOR_LEFT_PWM, 0);
    analogWrite(MOTOR_RIGHT_PWM, 0);
    digitalWrite(MOTOR_LEFT_DIR, LOW);
    digitalWrite(MOTOR_RIGHT_DIR, LOW);
  }

  void motorAction(int function)
  {
    switch (function)
    {
    case MOTORS_OFF:
      setMotorVolts(0, 0);
      break;
    case FORWARD_10:
      setMotorVolts(1.2, 1.2);
      break;
    case FORWARD_25:
      setMotorVolts(3.0, 3.0);
      break;
    case FORWARD_50:
      setMotorVolts(6.0, 6.0);
      break;
    case FORWARD_75:
      setMotorVolts(9.0, 9.0);
      break;
    case FORWARD_100:
      setMotorVolts(12.0, 12.0);
      break;
    case REVERSE_10:
      setMotorVolts(-1.2, -1.2);
      break;
    case REVERSE_25:
      setMotorVolts(-3.0, -3.0);
      break;
    case REVERSE_50:
      setMotorVolts(-6.0, -6.0);
      break;
    case REVERSE_75:
      setMotorVolts(-9.0, -9.0);
      break;
    case REVERSE_100:
      setMotorVolts(-12.0, -12.0);
      break;
    case SPIN_LEFT_25:
      setMotorVolts(-3.0, 3.0);
      break;
    case SPIN_LEFT_50:
      setMotorVolts(-6.0, 6.0);
      break;
    case SPIN_RIGHT_25:
      setMotorVolts(3.0, -3.0);
      break;
    case SPIN_RIGHT_50:
      setMotorVolts(6.0, -6.0);
      break;
    case PIVOT_LEFT_25:
      setMotorVolts(0, 3.0);
      break;
    case PIVOT_RIGHT_25:
      setMotorVolts(3.0, 0);
      break;
    case CURVE_LEFT:
      setMotorVolts(3.0, 6.0);
      break;
    case CURVE_RIGHT:
      setMotorVolts(6.0, 3.0);
      break;
    case BIG_CURVE_LEFT:
      setMotorVolts(6.0, 9.0);
      break;
    case BIG_CURVE_RIGHT:
      setMotorVolts(9.0, 6.0);
      break;
    default:
      setMotorVolts(0, 0);
      break;
    }
  }

private:
  void setLeftMotorPWM(int pwm)
  {
    pwm = constrain(pwm, -255, 255);
    if (pwm < 0)
    {
      digitalWrite(MOTOR_LEFT_DIR, HIGH);
      analogWrite(MOTOR_LEFT_PWM, -pwm);
    }
    else
    {
      digitalWrite(MOTOR_LEFT_DIR, LOW);
      analogWrite(MOTOR_LEFT_PWM, pwm);
    }
  }

  void setRightMotorPWM(int pwm)
  {
    pwm = constrain(pwm, -255, 255);
    if (pwm < 0)
    {
      digitalWrite(MOTOR_RIGHT_DIR, LOW);
      analogWrite(MOTOR_RIGHT_PWM, -pwm);
    }
    else
    {
      digitalWrite(MOTOR_RIGHT_DIR, HIGH);
      analogWrite(MOTOR_RIGHT_PWM, pwm);
    }
  }

  void setMotorPWM(int left, int right)
  {
    setLeftMotorPWM(left);
    setRightMotorPWM(right);
  }

  void setLeftMotorVolts(float volts)
  {
    volts = constrain(volts, -MAX_MOTOR_VOLTS, MAX_MOTOR_VOLTS);
    int motorPWM = (int)((255.0f * volts) / gBatteryVolts);
    setLeftMotorPWM(motorPWM);
  }

  void setRightMotorVolts(float volts)
  {
    volts = constrain(volts, -MAX_MOTOR_VOLTS, MAX_MOTOR_VOLTS);
    int motorPWM = (int)((255.0f * volts) / gBatteryVolts);
    setRightMotorPWM(motorPWM);
  }

  void setMotorVolts(float left, float right)
  {
    setLeftMotorVolts(left);
    setRightMotorVolts(right);
  }
};

#endif

// EOF
