#include <Arduino.h>
#include "cups.h"
#include "pinout.h"

int motor_freq = 100;
int servo_freq = 50;
int cups_resolution = 8;
int motorForwardChannel = 10;  // PWM channel for motor forward
int motorBackwardChannel = 11;  // PWM channel for motor backward
int servoLeftChannel = 12;  // PWM channel for servo
int servoRightChannel = 13;  // PWM channel for servo
int dutyCycleRightmost = (2.0/20)*255;
int dutyCycleNeutral = (1.5/20)*255;
int dutyCycleLeftmost = (1.0/20)*255;

void cupsSetup() {
    // Configure limit switch pins as input with internal pull-up resistors
    pinMode(CUP_A_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_A_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);

    // Configure motor control and servo pins as output
    pinMode(CUP_A_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_A_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_A_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_A_SERVO_RIGHT_PIN, OUTPUT);

    // Configure PWM channels
    ledcSetup(motorForwardChannel, motor_freq, cups_resolution);
    ledcSetup(motorBackwardChannel, motor_freq, cups_resolution);
    ledcSetup(servoLeftChannel, servo_freq, cups_resolution);
    ledcSetup(servoRightChannel, servo_freq, cups_resolution);

    // Attach PWM channels to the specified GPIO pins
    ledcAttachPin(CUP_A_MOTOR_FORWARD_PIN, motorForwardChannel);
    ledcAttachPin(CUP_A_MOTOR_BACKWARD_PIN, motorBackwardChannel);
    ledcAttachPin(CUP_A_SERVO_LEFT_PIN, servoLeftChannel);
    ledcAttachPin(CUP_A_SERVO_RIGHT_PIN, servoRightChannel);

    // Initialize duty cycle to 0% (motor and servo off)
    ledcWrite(motorForwardChannel, 0);
    ledcWrite(motorBackwardChannel, 0);
    ledcWrite(servoLeftChannel, dutyCycleRightmost); // Set servo all the way to right
    ledcWrite(servoRightChannel, dutyCycleLeftmost); // Set servo all the way to left
}

void extendCup(int cupNumber) {
    ledcWrite(motorForwardChannel, 255);  // Set motor to full speed forward
    while (digitalRead(CUP_A_EXTEND_LIMIT_SWITCH_PIN) == HIGH) { // TODO: use better, interrupt-based method later
        // Wait for limit switch to be triggered
    }
    ledcWrite(motorForwardChannel, 0);  // Stop the motor
}

void openCup(int cupNumber) {
    ledcWrite(servoLeftChannel, dutyCycleLeftmost);  // Set servo all the way to left #TODO: change this to exact amount needed
    ledcWrite(servoRightChannel, dutyCycleRightmost);  // Set servo all the way to right #TODO: change this to exact amount needed
}

void closeCup(int cupNumber) {
    ledcWrite(servoLeftChannel, dutyCycleRightmost);  // Set servo all the way to right
    ledcWrite(servoRightChannel, dutyCycleLeftmost);  // Set servo all the way to left
}

void retractCup(int cupNumber) {
    ledcWrite(motorBackwardChannel, 255);  // Set motor to full speed backward
    while (digitalRead(CUP_A_RETRACT_LIMIT_SWITCH_PIN) == HIGH) { // TODO: use better, interrupt-based method later
        // Wait for limit switch to be triggered
    }
    ledcWrite(motorBackwardChannel, 0);  // Stop the motor
}

void retractABit(int cupNumber) {
    ledcWrite(motorBackwardChannel, 255);  // Set motor to full speed backward
    delay(500);  // Wait for a bit
    ledcWrite(motorBackwardChannel, 0);  // Stop the motor
}
