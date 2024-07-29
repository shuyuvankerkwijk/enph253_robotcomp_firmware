#ifndef CORNER_SWITCHES_H
#define CORNER_SWITCHES_H

#include "globals.h"

void setup_switch_interrupts();

#define PIN_F_L PB5 // Front left switch pin
void handle_switch_F_L_Rising();
void handle_switch_F_L_Falling();

#define PIN_F_R PB4  // Front right switch pin
void handle_switch_F_R_Rising();
void handle_switch_F_R_Falling();

#define PIN_B_L PB3 // Back left switch pin
void handle_switch_B_L_Rising();
void handle_switch_B_L_Falling();

#define PIN_B_R PA15 // Back right switch pin
void handle_switch_B_R_Rising();
void handle_switch_B_R_Falling();

#endif