#ifndef GLOBAL_H
#define GLOBAL_H

/* --------------------------------- 
 * Define pins for the "high" 
 * (looking far ahead for speed
 * control) Linescanner 
 * --------------------------------- */
 // Arduino UNO
//#define syncHigh  12
//#define CLKHigh   11
//#define dataHigh  A0

// Teensy
#define syncHigh    A5
#define CLKHigh     A6
#define dataHigh    A4

/* --------------------------------- 
 * Define pins for the "low" 
 * (looking near for angle control) 
 * Linescanner 
 * --------------------------------- */
// Arduino UNO
//#define syncLow     10
//#define CLKLow      9
//#define dataLow     A1

// Teensy
#define syncLow     A8
#define CLKLow      A9
#define dataLow     A7

/* ---------------------------------
 * Define constants for control 
 * systems
 * --------------------------------- */
#define NUM_PIXELS  128
#define END         129
#define NONE        130
#define NOLINE      131

/* ---------------------------------
 * Define pins for components
 * --------------------------------- */
 // Arduino UNO
//#define SERVO_PIN   9
//#define MOTOR_PIN   3

// Teensy
#define SERVO_PIN     6
#define MOTOR_PIN     5

/* Degrees */
#define CENTER      90
#define LEFT        150
#define RIGHT       30

/* Calibration based on orientation of the scanner. Refer to vision diagram */
#define SETPOINT    64 
#define ADJACENT    65

#define NOT_YET_STR "Not yet implemented"

#define BTSerial Serial3

#endif
