#ifndef CORNER_SWITCHES_H
#define CORNER_SWITCHES_H

#include "globals.h"

void setup_switch_interrupts();

void handle_switch_F_L_Rising();
void handle_switch_F_L_Falling();

void handle_switch_F_R_Rising();
void handle_switch_F_R_Falling();

void handle_switch_B_L_Rising();
void handle_switch_B_L_Falling();

void handle_switch_B_R_Rising();
void handle_switch_B_R_Falling();

#endif