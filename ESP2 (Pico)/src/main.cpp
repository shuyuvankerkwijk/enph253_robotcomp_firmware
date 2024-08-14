#include <Arduino.h>
#include "esp1_uart.h"
#include "pinout.h"
#include "driver/ledc.h"
#include "driver/ledc.h"

String command = "";

void setup() {
  // set 'always up pins' to LOW
  pinMode(15, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(15, LOW);
  digitalWrite(0, LOW);
  digitalWrite(12, LOW);

  esp1UartSetup();
}

void loop() {
  
  command = esp1UartReceive();
  String lowerCommand = command;
  lowerCommand.toLowerCase();

  if (lowerCommand.indexOf("cupa") != -1) {
    esp1UartSend("Cup A command received");

    pinMode(CUP_A_EXTEND_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_A_RETRACT_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_A_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_A_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_A_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_A_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(2, 50, 8); // left servo
    ledcSetup(3, 50, 8); // right servo

    ledcAttachPin(CUP_A_SERVO_LEFT_PIN, 2);
    ledcAttachPin(CUP_A_SERVO_RIGHT_PIN, 3);

    // Extend cup A
    digitalWrite(CUP_A_MOTOR_FORWARD_PIN, HIGH);
    while(digitalRead(CUP_A_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
      delay(10);
    }
    digitalWrite(CUP_A_MOTOR_FORWARD_PIN, LOW);

    // Open Cup A
    ledcWrite(2, 18); // cup A left servo, set to 20 for open, 25 for close
    ledcWrite(3, 23); // cup A right servo, set to 21 for open, 15 for close
    delay(1000);

    // Close Cup A
    ledcWrite(2, 25); // cup A left servo, set to 20 for open, 25 for close
    ledcWrite(3, 15); // cup A right servo, set to 21 for open, 15 for close
    delay(1000);

    // Retract cup A
    digitalWrite(CUP_A_MOTOR_BACKWARD_PIN, HIGH);
    while(digitalRead(CUP_A_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      delay(10);
    }
    digitalWrite(CUP_A_MOTOR_BACKWARD_PIN, LOW);

  } else if (lowerCommand.indexOf("cupb") != -1) {
    esp1UartSend("Cup B command received");

    pinMode(CUP_B_EXTEND_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_B_RETRACT_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_B_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_B_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_B_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_B_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(6, 50, 8); // left servo
    ledcSetup(7, 50, 8); // right servo

    ledcAttachPin(CUP_B_SERVO_LEFT_PIN, 6);
    ledcAttachPin(CUP_B_SERVO_RIGHT_PIN, 7);

    // Extend cup B
    digitalWrite(CUP_B_MOTOR_FORWARD_PIN, HIGH);
    while(digitalRead(CUP_B_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
      delay(10);
    }
    digitalWrite(CUP_B_MOTOR_FORWARD_PIN, LOW);

    // Open Cup B
    ledcWrite(6, 18); // cup B left servo, set to 20 for open, 25 for close
    ledcWrite(7, 21); // cup B right servo, set to 19 for open, 14 for close
    delay(1000);

    // Close Cup B
    ledcWrite(6, 25); // cup B left servo, set to 20 for open, 25 for close
    ledcWrite(7, 14); // cup B right servo, set to 19 for open, 14 for close
    delay(1000);

    // Retract cup B
    digitalWrite(CUP_B_MOTOR_BACKWARD_PIN, HIGH);
    while(digitalRead(CUP_B_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
      delay(10);
    }
    digitalWrite(CUP_B_MOTOR_BACKWARD_PIN, LOW);

  } else if (lowerCommand.indexOf("cupc") != -1) {
    esp1UartSend("Cup C command received");

    pinMode(CUP_C_EXTEND_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_C_RETRACT_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_C_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_C_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_C_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_C_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(10, 50, 8); // left servo
    ledcSetup(11, 50, 8); // right servo

    ledcAttachPin(CUP_C_SERVO_LEFT_PIN, 10);
    ledcAttachPin(CUP_C_SERVO_RIGHT_PIN, 11);

    // Extend cup C
    digitalWrite(CUP_C_MOTOR_FORWARD_PIN, HIGH);
    while(digitalRead(CUP_C_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
      delay(10);
    }
    digitalWrite(CUP_C_MOTOR_FORWARD_PIN, LOW);

    // Open Cup C
    ledcWrite(10, 15); // cup C left servo, set to 17 for open, 25 for close
    ledcWrite(11, 22); // cup C right servo, set to 20 for open, 14.5 for close
    delay(1000);

    // Close Cup C
    ledcWrite(10, 25); // cup C left servo, set to 17 for open, 25 for close
    ledcWrite(11, 14.5); // cup C right servo, set to 20 for open, 14.5 for close
    delay(1000);

    // Retract cup C
    digitalWrite(CUP_C_MOTOR_BACKWARD_PIN, HIGH);
    while(digitalRead(CUP_C_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      delay(10);
    }
    digitalWrite(CUP_C_MOTOR_BACKWARD_PIN, LOW);

  } else if (lowerCommand.indexOf("cupd") != -1) {
    esp1UartSend("Cup D command received");

    pinMode(CUP_D_EXTEND_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_D_RETRACT_LIMIT_SWITCH_PIN, INPUT);
    pinMode(CUP_D_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(CUP_D_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(CUP_D_SERVO_LEFT_PIN, OUTPUT);
    pinMode(CUP_D_SERVO_RIGHT_PIN, OUTPUT);

    ledcSetup(14, 50, 8); // left servo
    ledcSetup(15, 50, 8); // right servo

    ledcAttachPin(CUP_D_SERVO_LEFT_PIN, 14);
    ledcAttachPin(CUP_D_SERVO_RIGHT_PIN, 15);

    // Extend cup D
    digitalWrite(CUP_D_MOTOR_FORWARD_PIN, HIGH);
    delay(1000);
    // while(digitalRead(CUP_D_EXTEND_LIMIT_SWITCH_PIN) == HIGH) {
    //   // wait for limit switch to be triggered
    //   delay(10);
    // }
    digitalWrite(CUP_D_MOTOR_FORWARD_PIN, LOW);

    // Open Cup D
    ledcWrite(14, 18); // cup D left servo, set to 20 for open, 26 for close
    ledcWrite(15, 21); // cup D right servo, set to 19 for open, 13 for close
    delay(1000);

    // Close Cup D
    ledcWrite(14, 26); // cup D left servo, set to 20 for open, 26 for close
    ledcWrite(15, 13); // cup D right servo, set to 19 for open, 13 for close
    delay(1000);

    // Retract cup D
    digitalWrite(CUP_D_MOTOR_BACKWARD_PIN, HIGH);
    while(digitalRead(CUP_D_RETRACT_LIMIT_SWITCH_PIN) == HIGH) {
      // wait for limit switch to be triggered
      delay(10);
    }
    digitalWrite(CUP_D_MOTOR_BACKWARD_PIN, LOW);

  } else {
    delay(10);
  }
}