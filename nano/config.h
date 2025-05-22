#ifndef CONFIG_H
#define CONFIG_H

// ----------- Pin Definitions -----------
#define START_SW 6
#define MOTOR_LEFT_DIR 7
#define MOTOR_RIGHT_DIR 8
#define MOTOR_LEFT_PWM 9
#define MOTOR_RIGHT_PWM 10
#define EMITTER_LEFT 11
#define EMITTER_RIGHT 12
#define LINE_LEFT A0
#define LINE_RIGHT A1
#define DIST_LEFT A2
#define DIST_MIDDLE A3
#define DIST_RIGHT A4
#define DIP_SW A5
#define BATTERY_VOLTS A6

// ----------- Hardware Constants -----------
#define MAX_MOTOR_VOLTS 12.0f
#define BATTERY_DIVIDER_RATIO 2.96f

// ----------- Serial -----------
#define SERIAL_BAUDRATE 9600

#endif

// EOF
