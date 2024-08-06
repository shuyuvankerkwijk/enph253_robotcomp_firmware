
//         // middle sensors on tape
//         if (pa1result > Reflectance_threshold){ //|| pa4result > Reflectance_threshold
//             for (int i=0; i<4; i++) {
//                 motorSpeeds[i] = 0;
//             }
//             Serial1.println("Middle sensors on tape");
//             run = false;
//             Serial1.println("run = false");
//         // front sensors on tape
//         } else if (pa0result > Reflectance_threshold){  //|| pa3result > Reflectance_threshold
//             for (int i=0; i<4; i++) {
//                 motorSpeeds[i] = 0;
//             }
//             Serial1.println("run = false");
//             Serial1.println("Front sensors on tape");
//         // back sensors on tape (reverse)
//         } else if (pa2result > Reflectance_threshold){ //|| pa5result > Reflectance_threshold
//             for (int i=0; i<4; i++) {
//                 motorSpeeds[i] = slowMotorSpeedsBackward[i];
//             }
//             Serial1.println("Back sensors on tape");
//         } else{
//             for (int i=0; i<4; i++) {
//                 motorSpeeds[i] = stdMotorSpeedsForwardRightAC[i];
//             }
//              Serial1.println("No sensors on tape");
//         }
//         updateMotorSpeed();
//         // delay(1000);
//     }else{
//         for(int i=0;i<4;i++){
//         motorSpeeds[i]=0;
//         }
//         updateMotorSpeed();
//     }
// }

#include <Arduino.h>
#include "parse.h"
#include "motor_control.h"
#include "map_encoding.h"
#include "globals.h"
#include "corner_switches.h"

Path* to_execute = new Path(begin_move, end_move);
HardwareSerial Serial3(PB11, PB10);

void setup() {
    // Set up motor PWM and digital outpuasc t pins for motor control
    setup_switch_interrupts();
    setupPWM();

    Serial3.begin(9600); // begin communication with ESP32

    for (int i = 0; i < 3; i++) {
        pinMode(sensor_pins_left[i], INPUT);
        pinMode(sensor_pins_right[i], INPUT);
    }
    pinMode(PC13,OUTPUT);
    digitalWrite(PC13,HIGH);
    delay(1000);
}


void loop() {

    if (Serial3.available()) {
        String message = Serial3.readStringUntil('\n');
        Serial3.println(parse(message));
    }
    if (run) {
        if (!begin_move.equalsIgnoreCase(end_move)&&(to_execute->done||to_execute==nullptr)) {
            delete to_execute;
            to_execute = new Path(begin_move, end_move);
        } else if (!to_execute->done) {
            Serial3.println("executing");
            to_execute->execute();
        }else{
            for(int i=0;i<4;i++){
                motorSpeeds[i]=0;
            }
        }
    }else{
        for(int i=0;i<4;i++){
            motorSpeeds[i]=0;
        }
    }
    updateMotorSpeed();
    Serial3.println("looped");
    delay(50);
}
