#ifndef CORNER_SWITCHES_H
#define CORNER_SWITCHES_H

#include "globals.h"

void setup_switch_interrupts();

#define PIN_F_R PA8
void handle_switch_F_R_Rising();
void handle_switch_F_R_Falling();
#define PIN_F_L PA9
void handle_switch_F_L_Rising();
void handle_switch_F_L_Falling();
#define PIN_B_R PA10
void handle_switch_B_R_Rising();
void handle_switch_B_R_Falling();
#define PIN_B_L PA11
void handle_switch_B_L_Rising();
void handle_switch_B_L_Falling();

#endif