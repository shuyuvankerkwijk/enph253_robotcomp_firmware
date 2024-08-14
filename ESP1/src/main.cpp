#include <Arduino.h>
// #include "ws.h"
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
    // wsSetup();
    // wsSend("Done with setup");
}

bool doneZB = false;
bool doneRB = false;
bool doneYB = false;
String bpMsg = "";

void loop() {
    // if (bpMsg != "") {
    //     wsSend("BP: " + bpMsg);
    // }
    doneZB = false;
    doneRB = false;
    doneYB = false;
    bpMsg = "";

    switch (robot_state) {
        case START:
            // wsSend("START");
            if (digitalRead(20) == 1) { 
                robot_state = TOMATO_DRIVE;
                // wsSend("Going to tomato");
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
                // wsSend("At tomato, turning Z");
            }
            break;

        case TOMATO_Z_CW:
            doneZB = craneMoveZB(72); // Turn to tomato position along Z (72 clicks CW from start position)
            if (doneZB) { 
                robot_state = TOMATO_EXTEND_R;
                craneSetDirectionRB(1); 
                // wsSend("Turned Z, extending R");
            }
            break;
        
        case TOMATO_EXTEND_R: 
            doneRB = craneMoveRB(0); // Move arm along R to position 0
            if (doneRB) {
                robot_state = TOMATO_EXTEND_Y;
                craneSetDirectionYB(1);
                // wsSend("Extended R, extending Y");
            }
            break;
        
        case TOMATO_EXTEND_Y:
            doneYB = craneMoveYB(1); // Extend arm down along Y
            if (doneYB) {
                vacuumOnB(255);
                delay(3000);
                robot_state = TOMATO_RETRACT_Y;
                craneSetDirectionYB(-1);
                // wsSend("Extended Y, retracting Y");
            }
            break;

        case TOMATO_RETRACT_Y:
            doneYB = craneMoveYB(-1); // Retract arm up along Y
            if (doneYB) {
                robot_state = TOMATO_TURN_Z;
                craneSetDirectionZB(-1); 
                // wsSend("Retracted Y, turning Z");
            }
            break;

        case TOMATO_TURN_Z:
            doneZB = craneMoveZB(-47); // Turn to cup D oriented position along Z 
            if (doneZB) {
                robot_state = TOMATO_RETRACT_R;
                craneSetDirectionRB(-1); 
                // wsSend("Turned Z, retracting R");
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
                // wsSend("Retracted R, going to lettuce");
            }
            break;

        case LETTUCE_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Lettuce") != -1) { 
                robot_state = LETTUCE_EXTEND_R;
                craneSetDirectionRB(1);
                // wsSend("At lettuce, extending R");
            }
            break;
        
        case LETTUCE_EXTEND_R:
            doneRB = craneMoveRB(0); // Move arm along R to position 0
            if (doneRB) {
                robot_state = LETTUCE_TURN_Z;
                craneSetDirectionZB(-1);
                // wsSend("Extended R, turning Z");
            }
            break;
        
        case LETTUCE_TURN_Z:
            doneZB = craneMoveZB(-10);
            if (doneZB) {
                robot_state = LETTUCE_EXTEND_Y;
                craneSetDirectionYB(1);
                // wsSend("Turned Z, extending Y");
            }
            break;

        case LETTUCE_EXTEND_Y:
            doneYB = craneMoveYB(1); // Extend arm down along Y
            if (doneYB) {
                vacuumOnB(255);
                delay(3000);
                robot_state = LETTUCE_RETRACT_Y;
                craneSetDirectionYB(-1);
                // wsSend("Extended Y, retracting Y");
            }
            break;

        case LETTUCE_RETRACT_Y:
            doneYB = craneMoveYB(-1); // Retract arm up along Y
            if (doneYB) {
                robot_state = LETTUCE_TURN_Z_2;
                craneSetDirectionZB(1);
                // wsSend("Retracted Y, turning Z");
            }
            break;
        
        case LETTUCE_TURN_Z_2:
            doneZB = craneMoveZB(10);
            if (doneZB) {
                robot_state = LETTUCE_RETRACT_R;
                craneSetDirectionRB(-1);
                // wsSend("Turned Z, retracting R");
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
                // wsSend("Retracted R, going to plate");
            }
            break;

        case PLATE_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Plates") != -1) {
                robot_state = PLATE_EXTEND_R;
                craneSetDirectionRB(1);
                // wsSend("At plate, extending R");
            }
            break;

        case PLATE_EXTEND_R:
            doneRB = craneMoveRB(0); 
            if (doneRB) {
                robot_state = PLATE_TURN_Z;
                craneSetDirectionZB(1);
                // wsSend("Extended R, turning Z");
            }
            break;

        case PLATE_TURN_Z:
            doneZB = craneMoveZB(50); // was 48 before
            if (doneZB) {
                robot_state = PLATE_EXTEND_Y;
                craneSetDirectionYB(1);
                // wsSend("Turned Z, extending Y");
            }
            break;
        
        case PLATE_EXTEND_Y:
            doneYB = craneMoveYB(1); 
            if (doneYB) {
                vacuumOnB(255);
                delay(3000);
                robot_state = PLATE_RETRACT_Y;
                craneSetDirectionYB(-1);
                // wsSend("Extended Y, retracting Y");
            }
            break;

        case PLATE_RETRACT_Y:
            doneYB = craneMoveYB(-1); 
            if (doneYB) {
                robot_state = SERVE_DRIVE;
                bluepillUartSend("ISAT:Plates");
                delay(10);
                bluepillUartSend("GOTO:Serving_area");
                // wsSend("Retracted Y, going to serve");
            }
            break;
        
        case SERVE_DRIVE:
            bpMsg = bluepillUartReceive();
            if (bpMsg.indexOf("ISAT:Serving_area") != -1) { 
                robot_state = SERVE_TURN_Z;
                craneSetDirectionZB(-1);
                // wsSend("At serving area, turning Z");
            }
            break;

        case SERVE_TURN_Z:
            doneZB = craneMoveZB(-47);
            if (doneZB) {
                robot_state = SERVE_RETRACT_R;
                craneSetDirectionRB(-1);
                // wsSend("Turned Z, Retracting R");
            }
            break;

        case SERVE_RETRACT_R:
            doneRB = craneMoveRB(-1); 
            if (doneRB) {
                robot_state = SERVE_EXTEND_Y;
                craneSetDirectionYB(1);
                // wsSend("Retracted R, extending Y");
            }
            break;

        case SERVE_EXTEND_Y:
            doneYB = craneMoveYB(1); 
            if (doneYB) {
                vacuumOffB();
                delay(3000);
                robot_state = SERVE_RETRACT_Y;
                craneSetDirectionYB(-1);
                // wsSend("Extended Y, retracting Y");
            }
            break;

        case SERVE_RETRACT_Y:
            doneYB = craneMoveYB(-1); 
            if (doneYB) {
                robot_state = SERVE_CUPS;
                // wsSend("Retracted Y, serving cups");
            }
            break;

        case SERVE_CUPS:
            // wsSend("Serving cups");
            esp2UartSend("CupD");
            delay(5000);
            robot_state = WAIT;
            break;

        case WAIT:
            // wsSend("WAIT");
            delay(50);
            break;

        default:
            break;
    }

}

// int switch_state_current = 0;
// int switch_state_previous = 0;
// unsigned long lastDebounceTime = 0;
// const unsigned long debounceDelay = 20; // Debounce time in milliseconds

//     // // read start switch
//     switch_state_previous = switch_state_current;
//     switch_state_current = digitalRead(20);

//     if (switch_state_current == LOW && switch_state_previous == HIGH) {
        
//     if (switch_state_current != switch_state_previous) {
//         lastDebounceTime = millis();
//     }

//   if ((millis() - lastDebounceTime) > debounceDelay) {
//     // if the switch reading has been stable for longer than the debounce delay, take it as the actual current state
//     if (reading != switch_state_current) {
//       switch_state_current = reading;

//       // Only if the current state is LOW and previous state was HIGH
//       if (switch_state_current == LOW && switch_state_previous == HIGH) {
//         // Your specific action when the switch goes from HIGH to LOW
//       }
//     }
//   }

    // // read start switch debounce
    // if(digitalRead(20)==HIGH){
    //     start_switch++;
    // }else if(start_switch>0){
    //     start_switch = 0;
    // }else{
    //     start_switch--;
    // }

    // // update based on start switch
    // if (start_switch == 5) {
    //     robot_state = START;
    // } else if (start_switch == -50) {
    //     robot_state = WAIT;
    // }





// // ZCW72
// // RF0
// // YD, vacuum on, YU
// // ZCCW26
// // RB95
// // vacuum off
// // RF0
// // ZCCW needs to move another 8 clicks (10?)
// // ZCW 8 clicks back
// // RB85
// // Z CW 65-8 (moved to 65 from position 8)
// // ZCCW move back to about 10
// //RB20


// 1. ZCW72 (from start pos to tomato pos)
// 2. ZCCW40 (from tomato pos to cup pos)
// 3. RB70 (retract to above cup from metal part lined up with back of slide)
// 4. RF56 (back out again to metal part lined up with back of slide)
// 5. ZCCW8 (from back out again pos to lettuce pos)
// 6. ZCW8
// 7. RB65, then RB5 to get above cup again
// 8. RF56 (back out again)
// 9. ZCW56 (to plate pos)
// 10. ZCCW53 to get plate in front of cup