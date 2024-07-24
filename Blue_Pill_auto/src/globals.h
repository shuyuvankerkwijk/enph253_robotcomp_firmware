#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <Arduino.h>
#include "path_progress.h"

// Declare global variables
extern int Reflectance_threshold;
extern bool switch_states[4];

// Forward declaration of Position class
class Position;

// Front house robot positions
extern Position Start;
extern Position Cheese;
extern Position Tomato;
extern Position Cutting;
extern Position Serving_Area;
extern Position Cooktop;
extern Position Plates;
extern Position Lettuce;

extern int motorSpeeds[4];
extern int stdMotorSpeedsRTL[4];
extern int stdMotorSpeedsLTR[4];
extern int stdMotorSpeedsAC[4];
extern int slowMotorSpeedsRTL[4];
extern int slowMotorSpeedsLTR[4];
extern int slowMotorSpeedsAC[4];


extern PinName sensor_pins_left[5];
extern PinName sensor_pins_right[5];

extern HardwareSerial Serial2;

extern bool run;

extern Position* current;
extern Position* goal;

#endif // GLOBALS_H
