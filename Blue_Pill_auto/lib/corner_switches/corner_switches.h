#ifndef CORNER_SWITCHES_H
#define CORNER_SWITCHES_H

#include "globals.h"

void setup_switch_interrupts();

void handle_switch_F_L();

void handle_switch_F_R();

void handle_switch_B_L();

void handle_switch_B_R();

#endif