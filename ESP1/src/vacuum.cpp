#include <Arduino.h>
#include "vacuum.h"
#include "main.h"
#include "pinout.h"

int vacuum_freq = 1000;
int resolution = 8;
int vacuumInChannelF = 6;  // PWM channel for vacuum in
int vacuumInChannelB = 7;  // PWM channel for vacuum in

void vacuumSetupF() {
    pinMode(VACUUM_FRONT_MOTOR_PIN, OUTPUT);
    ledcSetup(vacuumInChannelF, vacuum_freq, resolution);
    ledcAttachPin(VACUUM_FRONT_MOTOR_PIN, vacuumInChannelF);
    ledcWrite(vacuumInChannelF, 0);
}

void vacuumSetupB() {
    pinMode(VACUUM_BACK_MOTOR_PIN, OUTPUT);
    ledcSetup(vacuumInChannelB, vacuum_freq, resolution);
    ledcAttachPin(VACUUM_BACK_MOTOR_PIN, vacuumInChannelB);
    ledcWrite(vacuumInChannelB, 0);
}

void vacuumOnF(int power) {
    ledcWrite(vacuumInChannelF, power);  // Set vacuum to int power
}

void vacuumOffF() {
    ledcWrite(vacuumInChannelF, 0);  // Turn vacuum off
}

void vacuumOnB(int power) {
    ledcWrite(vacuumInChannelB, power);  // Set vacuum to int power
}

void vacuumOffB() {
    ledcWrite(vacuumInChannelB, 0);  // Turn vacuum off
}

