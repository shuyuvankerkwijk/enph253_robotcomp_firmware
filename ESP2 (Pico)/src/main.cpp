#include <Arduino.h>
#include "esp1_uart.h"
#include "pinout.h"
#include "driver/ledc.h"
#include "driver/ledc.h"


void setup() {
  pinMode(15, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(15, LOW);
  digitalWrite(0, LOW);
  digitalWrite(12, LOW);
  esp1UartSetup();
}

void loop() {

  String command = esp1UartReceive();
  if (command == "CupA") {
    pinMode(CUP_A_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_A_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_A_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_A_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_A_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_A_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(0, 100, 8); // forward motor
    ledcSetup(1, 100, 8); // backward motor
    ledcSetup(2, 50, 8); // left servo
    ledcSetup(3, 50, 8); // right servo
    ledcAttachPin(CUP_A_MOTOR_FORWARD_PIN, 0);
    ledcAttachPin(CUP_A_MOTOR_BACKWARD_PIN, 1);
    ledcAttachPin(CUP_A_SERVO_LEFT_PIN, 2);
    ledcAttachPin(CUP_A_SERVO_RIGHT_PIN, 3);

    // Extend cup A
    ledcWrite(0, 255);
    while(digitalRead(CUP_A_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(0, 0);

    // Open Cup A
    ledcWrite(2, 18); // cup A left servo, set to 20 for open, 25 for close
    ledcWrite(3, 23); // cup A right servo, set to 21 for open, 15 for close
    delay(1000);

    // Close Cup A
    ledcWrite(2, 25); // cup A left servo, set to 20 for open, 25 for close
    ledcWrite(3, 15); // cup A right servo, set to 21 for open, 15 for close
    delay(1000);

    // Retract cup A
    ledcWrite(1, 255);
    while(digitalRead(CUP_A_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(1, 0);

  } else if (command == "CupB") {
    pinMode(CUP_B_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_B_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_B_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_B_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_B_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_B_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(4, 100, 8); // forward motor
    ledcSetup(5, 100, 8); // backward motor
    ledcSetup(6, 50, 8); // left servo
    ledcSetup(7, 50, 8); // right servo
    ledcAttachPin(CUP_B_MOTOR_FORWARD_PIN, 4);
    ledcAttachPin(CUP_B_MOTOR_BACKWARD_PIN, 5);
    ledcAttachPin(CUP_B_SERVO_LEFT_PIN, 6);
    ledcAttachPin(CUP_B_SERVO_RIGHT_PIN, 7);

    // Extend cup B
    ledcWrite(4, 255);
    while(digitalRead(CUP_B_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(4, 0);

    // Open Cup B
    ledcWrite(6, 18); // cup B left servo, set to 20 for open, 25 for close
    ledcWrite(7, 21); // cup B right servo, set to 19 for open, 14 for close
    delay(1000);

    // Close Cup B
    ledcWrite(6, 25); // cup B left servo, set to 20 for open, 25 for close
    ledcWrite(7, 14); // cup B right servo, set to 19 for open, 14 for close
    delay(1000);

    // Retract cup B
    ledcWrite(5, 255);
    while(digitalRead(CUP_B_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(5, 0);

  } else if (command == "CupC") {
    pinMode(CUP_C_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_C_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_C_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_C_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_C_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_C_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(8, 100, 8); // forward motor
    ledcSetup(9, 100, 8); // backward motor
    ledcSetup(10, 50, 8); // left servo
    ledcSetup(11, 50, 8); // right servo
    ledcAttachPin(CUP_C_MOTOR_FORWARD_PIN, 8);
    ledcAttachPin(CUP_C_MOTOR_BACKWARD_PIN, 9);
    ledcAttachPin(CUP_C_SERVO_LEFT_PIN, 10);
    ledcAttachPin(CUP_C_SERVO_RIGHT_PIN, 11);

    // Extend cup C
    ledcWrite(8, 255);
    while(digitalRead(CUP_C_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(8, 0);

    // Open Cup C
    ledcWrite(10, 15); // cup C left servo, set to 17 for open, 25 for close
    ledcWrite(11, 22); // cup C right servo, set to 20 for open, 14.5 for close
    delay(1000);

    // Close Cup C
    ledcWrite(10, 25); // cup C left servo, set to 17 for open, 25 for close
    ledcWrite(11, 14.5); // cup C right servo, set to 20 for open, 14.5 for close
    delay(1000);

    // Retract cup C
    ledcWrite(9, 255);
    while(digitalRead(CUP_C_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(9, 0);

  } else if (command == "CupD") {
    pinMode(CUP_D_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_D_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(CUP_D_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_D_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_D_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_D_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(12, 100, 8); // forward motor
    ledcSetup(13, 100, 8); // backward motor
    ledcSetup(14, 50, 8); // left servo
    ledcSetup(15, 50, 8); // right servo

    ledcAttachPin(CUP_D_MOTOR_FORWARD_PIN, 12);
    ledcAttachPin(CUP_D_MOTOR_BACKWARD_PIN, 13);
    ledcAttachPin(CUP_D_SERVO_LEFT_PIN, 14);
    ledcAttachPin(CUP_D_SERVO_RIGHT_PIN, 15);

    // Extend cup D
    ledcWrite(12, 255);
    while(digitalRead(CUP_D_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(12, 0);

    // Open Cup D
    ledcWrite(14, 18); // cup D left servo, set to 20 for open, 26 for close
    ledcWrite(15, 21); // cup D right servo, set to 19 for open, 13 for close
    delay(1000);

    // Close Cup D
    ledcWrite(14, 26); // cup D left servo, set to 20 for open, 26 for close
    ledcWrite(15, 13); // cup D right servo, set to 19 for open, 13 for close
    delay(1000);

    // Retract cup D
    ledcWrite(13, 255);
    while(digitalRead(CUP_D_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
    }
    ledcWrite(13, 0);
  } else {
    esp1UartSend("Invalid command");
  }
}















// // void loop() {
// //   // String msg = bluepillUartReceive();
// //   // if (msg != "") {
// //   //   // wsSend(msg);
// //   //   Serial.println(msg);
// //   // }
// //   // delay(100);
// //   if (Serial1.available() > 0) {
// //     // Read the incoming data until a newline character is encountered
// //     String incomingData = Serial1.readStringUntil('\n');
    
// //     // Print the incoming data to Serial0 (USB to Serial)
// //     Serial.println(incomingData);
// //   }
// //   wsSend("message:"+String(i));
// //   delay(1000);
// //   i++;
// // }

// // const int gpioPins[] = {
// //   4,5,6,7,15,16,17,18,8,3,46,9,10,11,12,13,14,19,20,21,47,48,45,0,35,36,37,38,39,40,41,42,2,1
// // }; 

// // const int ledcChannel = 0;
// // const int pwmFrequency = 1000;  // 1 kHz
// // const int pwmResolution = 8;    // 8-bit resolution
// // const int pwmDutyCycle = 128;   // 50% duty cycle

// // void setup() {
//   // Serial.begin(115200);

//   // delay(5000);
//   // for (int i = 0; i < sizeof(gpioPins) / sizeof(gpioPins[0]); ++i) {
    
//   //   pinMode(gpioPins[i], OUTPUT);

//   //   // Configure and attach the PWM channel to the current pin
//   //   ledcSetup(ledcChannel, pwmFrequency, pwmResolution);
//   //   ledcAttachPin(gpioPins[i], ledcChannel);
//   //   ledcWrite(ledcChannel, pwmDutyCycle);

//   //   // Display the current GPIO pin being set
//   //   String message = "GPIO " + String(gpioPins[i]) + " set to HIGH (PWM)";
//   //   // oledDisplay(message);
//   //   Serial.println(message);

//   //   delay(100);  // Delay to observe the state change
//   // }
// // }