#include "corner_switches.h"
#include "globals.h"

void setup_switch_interrupts(){ // Corrected function name
    pinMode(switch_pins[0], INPUT_PULLUP);
    attachInterrupt((switch_pins[0]), handle_switch_F_L, CHANGE);
    pinMode(switch_pins[1], INPUT_PULLUP);
    attachInterrupt((switch_pins[1]), handle_switch_F_R, CHANGE);
    pinMode(switch_pins[2], INPUT_PULLUP);
    attachInterrupt((switch_pins[2]), handle_switch_B_L, CHANGE);
    pinMode(switch_pins[3], INPUT_PULLUP);
    attachInterrupt((switch_pins[3]), handle_switch_B_R, CHANGE);
}

void handle_switch_F_L(){
    switch_states[0] = !digitalRead(switch_pins[0]);
}

void handle_switch_F_R(){
    switch_states[1] = digitalRead(switch_pins[1]);
}

void handle_switch_B_L(){
    switch_states[2] = !digitalRead(switch_pins[2]);
}

void handle_switch_B_R(){
    switch_states[3] = digitalRead(switch_pins[3]);
}
