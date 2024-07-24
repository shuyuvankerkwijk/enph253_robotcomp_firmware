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

    Serial2.begin(9600); // begin communication with ESP32

    for (int i = 0; i < 5; i++) {
        pinMode(sensor_pins_left[i], INPUT_ANALOG);
        pinMode(sensor_pins_right[i], INPUT_ANALOG);
    }
}

void loop() {
    if (Serial2.available()) {
        char message[50];
        int length = Serial2.readBytesUntil('\n', message, sizeof(message) - 1);
        message[length] = '\0';
        Serial2.println(parse(message));
    }
    if (run) {
        if (!(current->equals(goal)) && (to_execute->done || to_execute==nullptr)) {
            delete to_execute; // fine to delete potential nullptr
            to_execute = current->calculate_path(goal);
        } else if (!to_execute->done) {
            to_execute->execute();
        }
    }
}
