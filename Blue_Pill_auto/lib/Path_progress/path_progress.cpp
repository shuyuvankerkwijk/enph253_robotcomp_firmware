#include "path_progress.h"
#include "globals.h"

void Left_to_right::run_cycle() {
    if (!right_crossed) {
        check_right_sensors();
        check_left_sensors();
        correct_motor_speeds();
    } else if (right_crossed) {
        check_left_sensors();
        correct_motor_speeds();
        // Additional logic for when the right side is crossed
    }
    if(left_crossed && switch_states[0]&&switch_states[2]){
        done = true;
    }
}

void Left_to_right::check_left_sensors() {
    for (int i = 0; i < 3; i++) {
        if (analogRead(sensor_pins_left[i]) > Reflectance_threshold) {
            left_sensors_crossed[i] = 1; // On tape
        } else {
            if (left_sensors_crossed[i] == 1) {
                left_sensors_crossed[i] = 2; // Crossed tape
            }
            else if (left_sensors_crossed[i] == 0) {
                left_sensors_crossed[i] = 0; // Before tape
            }
        }
    }
    left_crossed = ((left_sensors_crossed[0] == 2) &&
                    (left_sensors_crossed[1] == 2) &&
                    (left_sensors_crossed[2] == 2) );
}

void Left_to_right::check_right_sensors() {
    for (int i = 0; i < 3; i++) {
        if (analogRead(sensor_pins_right[i]) > Reflectance_threshold) {
            right_sensors_crossed[i] = 1; // On tape
        } else if (right_sensors_crossed[i] == 1) {
            right_sensors_crossed[i] = 2; // Crossed tape
        }
    }
    right_crossed = ((right_sensors_crossed[0] == 2) &&
                    (right_sensors_crossed[1] == 2) &&
                    (right_sensors_crossed[2] == 2));
}


void Left_to_right::correct_motor_speeds() {
    // 1. If none of right side sensors have crossed, then set motor speeds to standard LTR speeds
    if (!(right_sensors_crossed[0] || right_sensors_crossed[1] || right_sensors_crossed[2])) {
        for (int i = 0; i < 3; i++) {
            motorSpeeds[i] = stdMotorSpeedsLTR[i];
        }
    } 
    // 2. If one or more right side sensors are on tape or have crossed, correct for angle of crossing
    // else if (!(right_crossed || left_crossed)) {
    //     for (int i = 0; i < 3; i++) {
    //         motorSpeeds[i] = stdMotorSpeedsLTR[i];
    //     }
        

    // // 3. If all right side sensors have crossed, but not left side sensors, ??
    // }
    // else if (right_crossed && !left_crossed) {
    //     // TODO Implement logic for when right side is crossed but not left side -- nothing for now
    //     for (int i = 0; i < 3; i++) {
    //         motorSpeeds[i] = stdMotorSpeedsLTR[i];
    //     }
    // // 4. If all right side sensors have crossed and left side sensors have crossed, slow motors down
    // } 
    else if(right_crossed && left_crossed) {
        for (int i = 0; i < 3; i++) {
            motorSpeeds[i] = slowMotorSpeedsLTR[i];
        }
    }
}

void Right_to_left::run_cycle() {
    if (!left_crossed) {
        check_right_sensors();
        check_left_sensors();
        correct_motor_speeds();
    } else if (left_crossed) {
        check_left_sensors();
        correct_motor_speeds();
        // Additional logic for when the right side is crossed
    }
    if(right_crossed && switch_states[1]&&switch_states[3]){
        done = true;
    }
}

void Right_to_left::check_left_sensors() {
    // Implement sensor checking logic
}

void Right_to_left::check_right_sensors() {
    // Implement sensor checking logic
}

void Right_to_left::correct_motor_speeds() {
    // Implement motor speed correction logic
}

void Along_counter::run_cycle() {
    if (forward) {
        if (ac_left) {
            check_left_sensors();
        }
        // Implement forward movement logic
    } else if (backward) {
        // Implement backward movement logic
    }
}

void Along_counter::check_left_sensors() {
    for (int i = 0; i < 5; i++) {
        bool on = analogRead(sensor_pins_left[i] > Reflectance_threshold);
        if (on && left_sensors_on[i] == 0) {
            left_sensors_on[i] = 1; // Just touched tape
        } else if (on && left_sensors_on[i] == 1) {
            // nothing, still on tape
        } else if (!on && left_sensors_on[i] == 1) {
            left_sensors_on[i] = 0; // Just left tape
            left_sensors_num_crossed[i]++;
        }
    }
}

void Along_counter::check_right_sensors() {
    for (int i = 0; i < 5; i++) {
        bool on = analogRead(sensor_pins_right[i] > Reflectance_threshold);
        if (on && right_sensors_on[i] == 0) {
            right_sensors_on[i] = 1; // Just touched tape
        } else if (on && right_sensors_on[i] == 1) {
            // nothing, still on tape
        } else if (!on && right_sensors_on[i] == 1) {
            right_sensors_on[i] = 0; // Just left tape
            right_sensors_num_crossed[i]++;
        }
    }
}

void Along_counter::correct_motor_speeds() {
    if (forward) {

        if (ac_left) {

            // 1. If no sensors on tape or have crossed, set motor speeds to standard AC speeds
            if (!(left_sensors_on[0] || left_sensors_on[1] || left_sensors_on[2])
                && (left_sensors_num_crossed[0] == 0 && left_sensors_num_crossed[1] == 0 && left_sensors_num_crossed[2] == 0 && left_sensors_num_crossed[3] == 0 && left_sensors_num_crossed[4] == 0)) {
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = stdMotorSpeedsAC[i];
                }
            }

            // // 2. If foremost left sensor has crossed last tape marking, slow down motors
            // if (left_sensors_num_crossed[4] == (tape_markings-1)) { 
            //     for (int i = 0; i < 4; i++) {
            //         motorSpeeds[i] = slowMotorSpeedsAC[i];
            //     }
            // }

            // 3. If foremost left sensor has crossed desired tape marking or is on it, super slow motors
            if (left_sensors_num_crossed[4] == tape_markings || 
                (left_sensors_num_crossed[4] == (tape_markings-1) && left_sensors_on[4] == 1)) { // TODO TODO!!! TODO!!! check w/ benedikt if this is forward sensor and if tape_markings - 1 is correct
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = slowMotorSpeedsAC[i];
                }
            }

            // 5. If middle sensor has crossed last tape marking and is on tape, arrived where wanted
            if (left_sensors_num_crossed[2] == (tape_markings-1) && left_sensors_on[2] == 1) { // TODO add more checks for the other motors to ensure final destination
                done = true; // TODO instead, do fine adjustments to actually center on tape, otherwise why 3 sensors smh
            }
        
        } else if (ac_right) {
        // Implement motor speed correction logic
        }
    
    } else if (backward) {
        if (ac_left) {
            // Implement motor speed correction logic
        } else if (ac_right) {
            // Implement motor speed correction logic
        }
    }
}