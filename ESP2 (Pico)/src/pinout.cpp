#include "pinout.h"

int UART_ESP1_TX_PIN = 1; 
int UART_ESP1_RX_PIN = 3; 

int CUP_A_MOTOR_FORWARD_PIN = 13; 
int CUP_A_MOTOR_BACKWARD_PIN = 15; 
int CUP_A_SERVO_LEFT_PIN = 26; 
int CUP_A_SERVO_RIGHT_PIN = 33;
int CUP_A_EXTEND_LIMIT_SWITCH_PIN = 37; 
int CUP_A_RETRACT_LIMIT_SWITCH_PIN = 38;

int CUP_B_MOTOR_FORWARD_PIN = 2; 
int CUP_B_MOTOR_BACKWARD_PIN = 4; 
int CUP_B_SERVO_LEFT_PIN = 14; 
int CUP_B_SERVO_RIGHT_PIN = 20;
int CUP_B_EXTEND_LIMIT_SWITCH_PIN = 19; 
int CUP_B_RETRACT_LIMIT_SWITCH_PIN = 34;

int CUP_C_MOTOR_FORWARD_PIN = 7; 
int CUP_C_MOTOR_BACKWARD_PIN = 5; 
int CUP_C_SERVO_LEFT_PIN = 25; 
int CUP_C_SERVO_RIGHT_PIN = 27;
int CUP_C_EXTEND_LIMIT_SWITCH_PIN = 21; 
int CUP_C_RETRACT_LIMIT_SWITCH_PIN = 35;

int CUP_D_MOTOR_FORWARD_PIN = 10; 
int CUP_D_MOTOR_BACKWARD_PIN = 9; 
int CUP_D_SERVO_LEFT_PIN = 12; 
int CUP_D_SERVO_RIGHT_PIN = 32;
int CUP_D_EXTEND_LIMIT_SWITCH_PIN = 22; 
int CUP_D_RETRACT_LIMIT_SWITCH_PIN = 8;


//7, 5, 10, 9
//4, 2, 15, 13

// void setup() {
//   Serial.begin(9600);
//   pinMode(7, OUTPUT);//cup 3 forward good -- extend switch on 21, retract switch on 35
//   pinMode(5, OUTPUT);// cup 3 backward good
//   pinMode(10, OUTPUT);// cup 4 forward good -- extend switch on 22, retract switch on 8
//   pinMode(9, OUTPUT);// cup 4 backward good
//   pinMode(4, OUTPUT);//cup 2 backward good
//   pinMode(2, OUTPUT);//cup 2 forward good -- extend switch on 19, retract switch on 34
//   pinMode(15, OUTPUT);//cup 1 backward good
//   pinMode(13, OUTPUT);//cup 1 forward good -- works great, extend switch on 37, retract switch on 38

//   pinMode(12, OUTPUT); // 4th from left
//   pinMode(14, OUTPUT); // 8th from left
//   pinMode(27, OUTPUT); // 1st from left
//   pinMode(33, OUTPUT); // 6th from left
//   pinMode(32, OUTPUT); // 3rd from left
//   pinMode(26, OUTPUT); // 5th from left
//   pinMode(25, OUTPUT); // 2nd from left
//   pinMode(20, OUTPUT); // 7th from left

//   ledcSetup(0, 250, 8); 
//   ledcAttachPin(5, 0);
//   ledcWrite(0, 255); 

  // ledcSetup(0, 50, 8); // 50Hz = 20 ms duty cycle
  // ledcAttachPin(14, 0);
  // ledcWrite(0, 25); // 13 = 1ms, 26 = 2ms

  // ledcSetup(1, 50, 8); // 50Hz = 20 ms duty cycle
  // ledcAttachPin(20, 1);
  // ledcWrite(1, 14); // 13 = 1ms, 26 = 2ms

  // cup 3 left servo (pin 25) -- set to 25 for home position, 17 for open
  // cup 3 right servo (pin 27) -- set to 14.5 for home position, 20 for open

  // cup 4 left servo (pin 12) -- set to  26 for home position, 20 for open
  // cup 4 right servo (pin 32) -- set to 13 for home position, 19 for open

  // cup 2 left servo (14) -- set to 25 for home position, 20 for open
  // cup 2 right servo (20) -- set to 14 for home position, 19 for open

  // cup 1 left servo (26) -- set to 25 for home position, 20 for open
  // cup 1 right servo (33) -- set to 15 for home position, 21 for open

  // 38 -- cup 1 back switch
  // 37 - cup 1 front switch