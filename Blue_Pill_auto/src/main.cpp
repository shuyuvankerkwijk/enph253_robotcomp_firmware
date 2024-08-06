
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
    delay(3);
}
