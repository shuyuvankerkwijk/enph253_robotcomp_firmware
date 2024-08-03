#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <Arduino.h>
#include "path_progress.h"

// Declare global variables

// extern HardwareSerial Serial1;
extern HardwareSerial Serial_to_ESP;

extern int Reflectance_threshold;
extern bool switch_states[4];

extern PinName motor_pwm_pins[4]; 
extern int motor_pwm_pins_ints[4];
extern int motor_d_select_pins[4];
extern int switch_pins[4];
extern int sensor_pins_left[3];
extern int sensor_pins_right[3];

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
extern int slowMotorSpeedsBackwardRightAC[4];



extern bool run;

extern String begin_move;
extern String end_move;


#endif // GLOBALS_H