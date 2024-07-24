#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "stm32f1xx.h"
#include "globals.h"
#include "stm32f1xx_hal.h"

void updateMotorSpeed();
void setupPWM();

#endif