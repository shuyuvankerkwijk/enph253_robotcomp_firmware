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
extern Position Positions[8];

extern int motorSpeeds[4];
extern int stdMotorSpeedsRTL[4];
extern int stdMotorSpeedsLTR[4];
extern int stdMotorSpeedsForward[4];
extern int stdMotorSpeedsBackward[4];

extern int stdMotorSpeedsForwardLeftAC[4];
extern int stdMotorSpeedsForwardRightAC[4];
extern int stdMotorSpeedsBackwardLeftAC[4];
extern int stdMotorSpeedsBackwardRightAC[4];

extern int slowMotorSpeedsRTL[4];
extern int slowMotorSpeedsLTR[4];
extern int slowMotorSpeedsForward[4];
extern int slowMotorSpeedsBackward[4];

extern int slowMotorSpeedsForwardLeftAC[4];
extern int slowMotorSpeedsForwardRightAC[4];
extern int slowMotorSpeedsBackwardLeftAC[4];
extern int slowMotorSpeedBackwardRightAC[4];

extern PinName sensor_pins_left[5];
extern PinName sensor_pins_right[5];

extern bool run;

extern Position* current;
extern Position* goal;

#endif // GLOBALS_H
