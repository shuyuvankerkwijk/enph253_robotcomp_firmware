#include "pinout.h"

int START_SWITCH_PIN = 100; // ??

int UART_BLUEPILL_TX_PIN = 43; 
int UART_BLUEPILL_RX_PIN = 44; 

int UART_ESP2_RX_PIN = 18;
int UART_ESP2_TX_PIN = 17;

//Front arm
int VACUUM_FRONT_MOTOR_PIN = 100; // ?

int ZMOTOR_FRONT_CW_PIN = 48;
int ZMOTOR_FRONT_CCW_PIN = 0;
int ZMOTOR_FRONT_ENCODER_PIN = 100; // ?
int ZMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN = 100; // ?

int RMOTOR_FRONT_FORWARD_PIN = 100; // ?
int RMOTOR_FRONT_BACKWARD_PIN = 100; // ?
int RMOTOR_FRONT_ENCODER_PIN = 100; // ?
int RMOTOR_FRONT_ENCODER_PIN_B = 100; // ? 
int RMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN = 100; // ?

int YMOTOR_FRONT_UP_PIN = 100; // ?
int YMOTOR_FRONT_DOWN_PIN = 100; // ?
int YMOTOR_FRONT_EXTEND_LIMIT_SWITCH_PIN = 100; // ?
int YMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN = 100; // ?

//Back arm
int VACUUM_BACK_MOTOR_PIN = 14;

int ZMOTOR_BACK_CW_PIN = 47;
int ZMOTOR_BACK_CCW_PIN = 21;
int ZMOTOR_BACK_ENCODER_PIN = 40;  // 40
// int ZMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN = 100; // ?

int RMOTOR_BACK_FORWARD_PIN = 10;
int RMOTOR_BACK_BACKWARD_PIN = 11;
int RMOTOR_BACK_ENCODER_PIN = 38; // 38
int RMOTOR_BACK_ENCODER_PIN_B = 20; 
// int RMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN = 100; // ?

int YMOTOR_BACK_UP_PIN = 12;
int YMOTOR_BACK_DOWN_PIN = 13;
int YMOTOR_BACK_EXTEND_LIMIT_SWITCH_PIN = 2;
int YMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN = 39;

// pinMode(40, INPUT);
// attachInterrupt(digitalPinToInterrupt(40), zencoding, RISING);

// pinMode(21, OUTPUT); // back arm counterclockwise
// pinMode(47, OUTPUT); // back arm clockwise
// pinMode(48, OUTPUT); // front arm clockwise
// pinMode(0, OUTPUT); // front arm counterclockwise

// analogWrite(21, 255);
// analogWrite(47, 255);
// analogWrite(48, 255);
// analogWrite(0, 255);

// pinMode(13, OUTPUT); // back arm down
// pinMode(12, OUTPUT); // back arm up

// pinMode(11, OUTPUT); // back arm backwards
// pinMode(10, OUTPUT); // back arm forwards

// pinMode(14, OUTPUT); // back arm vacuum
