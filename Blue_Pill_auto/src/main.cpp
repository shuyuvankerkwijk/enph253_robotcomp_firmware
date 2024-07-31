// #include <Arduino.h>
// #include "motor_control.h"
// #include "globals.h"

// #include "stm32f1xx_hal.h"
// #include "stm32f1xx_hal_rcc.h"
// #include "stm32f1xx_hal_gpio.h"

// void setup() {
//     setupPWM();
//     Serial1.begin(9600); // begin communication with ESP32
//     pinMode(PA0, INPUT_ANALOG); // right front
//     pinMode(PA1, INPUT_ANALOG); // right middle
//     pinMode(PA2, INPUT_ANALOG); // right back
//     pinMode(PA3, INPUT_ANALOG); // left front
//     pinMode(PA4, INPUT_ANALOG); // left middle
//     pinMode(PA5, INPUT_ANALOG); // left back
//     for (int i=0; i<4; i++) {
//         motorSpeeds[i] = stdMotorSpeedsForward[i];
//     }
//     updateMotorSpeed();
// }

// void loop() {
//     if(run){
//         int pa0result = analogRead(PA0);
//         int pa1result = analogRead(PA1);
//         int pa2result = analogRead(PA2);
//         int pa3result = analogRead(PA3);
//         int pa4result = analogRead(PA4);
//         int pa5result = analogRead(PA5);

//         Serial1.print("Sensor values:");
//         Serial1.print(String(pa0result)+",");
//         Serial1.print(String(pa1result)+",");
//         Serial1.print(String(pa2result)+",");
//         Serial1.print(String(pa3result)+",");
//         Serial1.print(String(pa4result)+",");
//         Serial1.println(String(pa5result));

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
//             run = false;
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

// Include HAL headers
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_hal_gpio.h"

Path* to_execute = nullptr;

void setup() {
    // Set up motor PWM and digital output pins for motor control
    setup_switch_interrupts();
    setupPWM();
    updateMotorSpeed();

    Serial1.begin(9600); // begin communication with ESP32

    for (int i = 0; i < 5; i++) {
        pinMode(sensor_pins_left[i], INPUT_ANALOG);
        pinMode(sensor_pins_right[i], INPUT_ANALOG);
    }
}

void loop() {
    if (Serial1.available()) {
        char message[50];
        int length = Serial2.readBytesUntil('\n', message, sizeof(message) - 1);
        message[length] = '\0';
        Serial1.println(parse(message));
    }
    if (run) {
        if (!(current->equals(goal)) && (to_execute->done || to_execute==nullptr)) {
            delete to_execute;
            to_execute = current->calculate_path(goal);
        } else if (!to_execute->done) {
            to_execute->execute();
        }
    }else{
        for(int i=0;i<4;i++){
            motorSpeeds[i]=0;
        }
    }
    updateMotorSpeed();
}
