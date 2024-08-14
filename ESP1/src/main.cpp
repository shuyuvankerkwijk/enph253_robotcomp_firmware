#include <Arduino.h>
#include "crane.h"
#include "bluepill_uart.h"
#include "esp2_uart.h"
#include "vacuum.h"
#include "pinout.h"
#include "driver/ledc.h"

enum RobotState {
  START,
  TOMATO_DRIVE,
  TOMATO_Z_CW,
  TOMATO_EXTEND_R,
  TOMATO_EXTEND_Y,
  TOMATO_RETRACT_Y,
  TOMATO_TURN_Z,
  TOMATO_RETRACT_R,
  LETTUCE_DRIVE,
  LETTUCE_EXTEND_R, 
  LETTUCE_TURN_Z,
  LETTUCE_EXTEND_Y,
  LETTUCE_RETRACT_Y,
  LETTUCE_TURN_Z_2,
  LETTUCE_RETRACT_R,
  PLATE_DRIVE,
  PLATE_EXTEND_R,
  PLATE_TURN_Z,
  PLATE_EXTEND_Y,
  PLATE_RETRACT_Y,
  SERVE_DRIVE,
  SERVE_TURN_Z,
  SERVE_RETRACT_R,
  SERVE_EXTEND_Y,
  SERVE_RETRACT_Y,
  SERVE_CUPS,
  WAIT
};

RobotState robot_state = START;

void setup() {
    // These pins default high, so start by setting them low
    pinMode(14, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(39, OUTPUT);
    digitalWrite(14, LOW);
    digitalWrite(20, LOW);
    digitalWrite(0, LOW);
    digitalWrite(39, LOW); 

    // Start button
    pinMode(20, INPUT_PULLDOWN); 

    bluepillUartSetup();
    esp2UartSetup();
    vacuumSetupB();
    craneSetupB();
}

bool doneZB = false;
bool doneRB = false;
bool doneYB = false;
String bpMsg = "";

void loop() {

    doneZB = false;
    doneRB = false;
    doneYB = false;
    bpMsg = "";

    switch (robot_state) {
        case START:
            if (digitalRead(20) == 1) { 
                robot_state = TOMATO_DRIVE;
                bluepillUartSend("ISAT:Start");
                delay(10);
                bluepillUartSend("GOTO:Tomato");
            } else {
                delay(50);
            }
            break;

        case TOMATO_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Tomato") != -1) { 
                robot_state = TOMATO_Z_CW;
                craneSetDirectionZB(1); 
            }
            break;

        case TOMATO_Z_CW:
            doneZB = craneMoveZB(72); // Turn to tomato position along Z (72 clicks CW from start position)
            if (doneZB) { 
                robot_state = TOMATO_EXTEND_R;
                craneSetDirectionRB(1); 
            }
            break;
        
        case TOMATO_EXTEND_R: 
            doneRB = craneMoveRB(0); // Move arm along R to position 0
            if (doneRB) {
                robot_state = TOMATO_EXTEND_Y;
                craneSetDirectionYB(1);
            }
            break;
        
        case TOMATO_EXTEND_Y:
            doneYB = craneMoveYB(1); // Extend arm down along Y
            if (doneYB) {
                vacuumOnB(255);
                delay(3000);
                robot_state = TOMATO_RETRACT_Y;
                craneSetDirectionYB(-1);
            }
            break;

        case TOMATO_RETRACT_Y:
            doneYB = craneMoveYB(-1); // Retract arm up along Y
            if (doneYB) {
                robot_state = TOMATO_TURN_Z;
                craneSetDirectionZB(-1); 
            }
            break;

        case TOMATO_TURN_Z:
            doneZB = craneMoveZB(-47); // Turn to cup D oriented position along Z 
            if (doneZB) {
                robot_state = TOMATO_RETRACT_R;
                craneSetDirectionRB(-1); 
            }
            break;

        case TOMATO_RETRACT_R:
            doneRB = craneMoveRB(-90); // 87??? // Move arm inwards to position -90 along R (90 clicks inward from fully extended)
            if (doneRB) {
                vacuumOffB();
                delay(3000);
                robot_state = LETTUCE_DRIVE;
                bluepillUartSend("ISAT:Tomato");
                delay(10);
                bluepillUartSend("GOTO:Lettuce");
            }
            break;

        case LETTUCE_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Lettuce") != -1) { 
                robot_state = LETTUCE_EXTEND_R;
                craneSetDirectionRB(1);
            }
            break;
        
        case LETTUCE_EXTEND_R:
            doneRB = craneMoveRB(0); // Move arm along R to position 0
            if (doneRB) {
                robot_state = LETTUCE_TURN_Z;
                craneSetDirectionZB(-1);
            }
            break;
        
        case LETTUCE_TURN_Z:
            doneZB = craneMoveZB(-10);
            if (doneZB) {
                robot_state = LETTUCE_EXTEND_Y;
                craneSetDirectionYB(1);
            }
            break;

        case LETTUCE_EXTEND_Y:
            doneYB = craneMoveYB(1); // Extend arm down along Y
            if (doneYB) {
                vacuumOnB(255);
                delay(3000);
                robot_state = LETTUCE_RETRACT_Y;
                craneSetDirectionYB(-1);
            }
            break;

        case LETTUCE_RETRACT_Y:
            doneYB = craneMoveYB(-1); // Retract arm up along Y
            if (doneYB) {
                robot_state = LETTUCE_TURN_Z_2;
                craneSetDirectionZB(1);
            }
            break;
        
        case LETTUCE_TURN_Z_2:
            doneZB = craneMoveZB(10);
            if (doneZB) {
                robot_state = LETTUCE_RETRACT_R;
                craneSetDirectionRB(-1);
            }
            break;

        case LETTUCE_RETRACT_R:
            doneRB = craneMoveRB(-85); 
            if (doneRB) {
                vacuumOffB();
                delay(3000);
                robot_state = PLATE_DRIVE;
                bluepillUartSend("ISAT:Lettuce");
                delay(10);
                bluepillUartSend("GOTO:Plates");
            }
            break;

        case PLATE_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Plates") != -1) {
                robot_state = PLATE_EXTEND_R;
                craneSetDirectionRB(1);
            }
            break;

        case PLATE_EXTEND_R:
            doneRB = craneMoveRB(0); 
            if (doneRB) {
                robot_state = PLATE_TURN_Z;
                craneSetDirectionZB(1);
            }
            break;

        case PLATE_TURN_Z:
            doneZB = craneMoveZB(50); // was 48 before
            if (doneZB) {
                robot_state = PLATE_EXTEND_Y;
                craneSetDirectionYB(1);
            }
            break;
        
        case PLATE_EXTEND_Y:
            doneYB = craneMoveYB(1); 
            if (doneYB) {
                vacuumOnB(255);
                delay(3000);
                robot_state = PLATE_RETRACT_Y;
                craneSetDirectionYB(-1);
            }
            break;

        case PLATE_RETRACT_Y:
            doneYB = craneMoveYB(-1); 
            if (doneYB) {
                robot_state = SERVE_DRIVE;
                bluepillUartSend("ISAT:Plates");
                delay(10);
                bluepillUartSend("GOTO:Serving_area");
            }
            break;
        
        case SERVE_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Serving_area") != -1) { 
                robot_state = SERVE_TURN_Z;
                craneSetDirectionZB(-1);
            }
            break;

        case SERVE_TURN_Z:
            doneZB = craneMoveZB(-47);
            if (doneZB) {
                robot_state = SERVE_RETRACT_R;
                craneSetDirectionRB(-1);
            }
            break;

        case SERVE_RETRACT_R:
            doneRB = craneMoveRB(-1); 
            if (doneRB) {
                robot_state = SERVE_EXTEND_Y;
                craneSetDirectionYB(1);
            }
            break;

        case SERVE_EXTEND_Y:
            doneYB = craneMoveYB(1); 
            if (doneYB) {
                vacuumOffB();
                delay(3000);
                robot_state = SERVE_RETRACT_Y;
                craneSetDirectionYB(-1);
            }
            break;

        case SERVE_RETRACT_Y:
            doneYB = craneMoveYB(-1); 
            if (doneYB) {
                robot_state = SERVE_CUPS;
            }
            break;

        case SERVE_CUPS:
            esp2UartSend("CupD");
            delay(5000);
            robot_state = WAIT;
            break;

        case WAIT:
            delay(50);
            break;

        default:
            break;
    }

}