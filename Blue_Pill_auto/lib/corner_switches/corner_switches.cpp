#include "corner_switches.h"
#include "globals.h"

void setup_switch_interrupts(){ // Corrected function name
    pinMode(PIN_F_R, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_F_R), handle_switch_F_R_Rising, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_F_R), handle_switch_F_R_Falling, FALLING);
    pinMode(PIN_F_L, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_F_L), handle_switch_F_L_Rising, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_F_L), handle_switch_F_L_Falling, FALLING);
    pinMode(PIN_B_R, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_B_R), handle_switch_B_R_Rising, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_B_R), handle_switch_B_R_Falling, FALLING);
    pinMode(PIN_B_L, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_B_L), handle_switch_B_L_Rising, RISING);
    attachInterrupt(digitalPinToInterrupt(PIN_B_L), handle_switch_B_L_Falling, FALLING);
}

void handle_switch_F_R_Rising(){
    switch_states[0] = false;
}
void handle_switch_F_R_Falling(){
    switch_states[0] = true;
}

void handle_switch_F_L_Rising(){
    switch_states[1] = false;
}
void handle_switch_F_L_Falling(){
    switch_states[1] = true;
}

void handle_switch_B_R_Rising(){
    switch_states[2] = false;
}
void handle_switch_B_R_Falling(){
    switch_states[2] = true;
}

void handle_switch_B_L_Rising(){
    switch_states[3] = false;
}
void handle_switch_B_L_Falling(){
    switch_states[3] = true;
}
