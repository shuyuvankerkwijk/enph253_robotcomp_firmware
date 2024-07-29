#ifndef CORNER_SWITCHES_H
#define CORNER_SWITCHES_H

#include "globals.h"

void setup_switch_interrupts();

#define PIN_F_R PB5
void handle_switch_F_R_Rising();
void handle_switch_F_R_Falling();
#define PIN_F_L //TODO
void handle_switch_F_L_Rising();
void handle_switch_F_L_Falling();
#define PIN_B_R PB3
void handle_switch_B_R_Rising();
void handle_switch_B_R_Falling();
#define PIN_B_L PA15
void handle_switch_B_L_Rising();
void handle_switch_B_L_Falling();

#endif