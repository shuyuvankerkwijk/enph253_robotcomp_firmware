#include <Arduino.h>
#include "globals.h"
#include "motor_control.h"

void setup() {
    pinMode(PC13, OUTPUT);
    setupPWM();
    // Serial1.begin(9600); // begin communication with ESP32
    pinMode(PA0, INPUT_ANALOG); // right front
    pinMode(PA1, INPUT_ANALOG); // right middle
    pinMode(PA2, INPUT_ANALOG); // right back
    pinMode(PA3, INPUT_ANALOG); // left front
    pinMode(PA4, INPUT_ANALOG); // left middle
    pinMode(PA5, INPUT_ANALOG); // left back
    for (int i=0; i<4; i++) {
        motorSpeeds[i] = stdMotorSpeedsForward[i];
    }
}

void loop() {
    digitalWrite(PC13, LOW);

    int pa0result = analogRead(PA0);
    int pa1result = analogRead(PA1);
    int pa2result = analogRead(PA2);
    int pa3result = analogRead(PA3);
    int pa4result = analogRead(PA4);
    int pa5result = analogRead(PA5);

    // front sensors on tape
    if (pa0result > Reflectance_threshold || pa3result > Reflectance_threshold){
        digitalWrite(PC13, HIGH);
        for (int i=0; i<4; i++) {
            motorSpeeds[i] = slowMotorSpeedsForward[i];
        }
        delay(100);
    }

    // middle sensors on tape
    if (pa1result > Reflectance_threshold || pa4result > Reflectance_threshold){
        digitalWrite(PC13, HIGH);
        for (int i=0; i<4; i++) {
            motorSpeeds[i] = 0;
        }
        delay(100);
    }

    // back sensors on tape (reverse)
    if (pa2result > Reflectance_threshold || pa5result > Reflectance_threshold){
        digitalWrite(PC13, HIGH);
        for (int i=0; i<4; i++) {
            motorSpeeds[i] = slowMotorSpeedsBackward[i];
        }
        delay(100);
    }

    Serial1.println("PA0" + pa0result);
    Serial1.println("PA1" + pa1result);
    Serial1.println("PA2" + pa2result);
    Serial1.println("PA3" + pa3result);
    Serial1.println("PA4" + pa4result);
    Serial1.println("PA5" + pa5result);
}

// #include <Arduino.h>
// #include "parse.h"
// #include "motor_control.h"
// #include "map_encoding.h"
// #include "globals.h"
// #include "corner_switches.h"

// // Include HAL headers
// #include "stm32f1xx_hal.h"
// #include "stm32f1xx_hal_rcc.h"
// #include "stm32f1xx_hal_gpio.h"

// Path* to_execute = nullptr;

// void setup() {
//     // Set up motor PWM and digital output pins for motor control
//     setup_switch_interrupts();
//     setupPWM();
//     updateMotorSpeed();

//     Serial2.begin(9600); // begin communication with ESP32

//     for (int i = 0; i < 5; i++) {
//         pinMode(sensor_pins_left[i], INPUT_ANALOG);
//         pinMode(sensor_pins_right[i], INPUT_ANALOG);
//     }
// }

// void loop() {
//     if (Serial2.available()) {
//         char message[50];
//         int length = Serial2.readBytesUntil('\n', message, sizeof(message) - 1);
//         message[length] = '\0';
//         Serial2.println(parse(message));
//     }
//     if (run) {
//         if (!(current->equals(goal)) && (to_execute->done || to_execute==nullptr)) {
//             delete to_execute;
//             to_execute = current->calculate_path(goal);
//         } else if (!to_execute->done) {
//             to_execute->execute();
//         }
//     }else{
//         for(int i=0;i<4;i++){
//             motorSpeeds[i]=0;
//         }
        
//     }
//     updateMotorSpeed();
// }
