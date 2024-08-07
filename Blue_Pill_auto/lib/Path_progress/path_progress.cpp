#include "path_progress.h"
#include "globals.h"
#include "Arduino.h"

Left_to_right::Left_to_right(bool start){
    int right_sensors_crossed[3] = {0,0,0}; // 0 is before, 1 is on, and 2 is crossed
    bool right_crossed = start;
    int left_sensors_crossed[3] = {0,0,0};
    bool left_crossed = false;
}

void Left_to_right::execute() {
    Serial3.println("LTR");
    if (!right_crossed) {
        check_right_sensors();
    } else if (right_crossed&&!left_crossed) {
        check_left_sensors();
    }
    correct_motor_speeds();
    if(left_crossed && right_crossed && (switch_states[1] || switch_states[3])){ // if both sides crossed and  one of the switches on the right side clicked, succesfully crossed
        done = true;
        for(int i = 0; i<4;i++){
            motorSpeeds[i] = 0;
        }
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
    if (!right_crossed&&!left_crossed) {
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = stdMotorSpeedsLTR[i];
        }
    } 
    // // 2. If all right side sensors have crossed but the left have not yet, then set the motor speeds to standard LTR speeds
    else if (right_crossed && !left_crossed) {
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = stdMotorSpeedsLTR[i];
        }
    }

    // 3. If all right side sensors have crossed and left side sensors have crossed, slow motors down
    else if(right_crossed && left_crossed) {
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = slowMotorSpeedsLTR[i];
        }
    }

    // 4. if all the sensors have crossed and one of the counter detection switches was pressed set to 0 and finish
    else if((right_crossed && left_crossed)&&(switch_states[1]||switch_states[3])){
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = slowMotorSpeedsLTR[i];
        }
        done = true;
        Serial3.println("LTR: DONE");
    }
}

Right_to_left::Right_to_left(bool start){
    int right_sensors_crossed[3] = {0,0,0}; // 0 is before, 1 is on, and 2 is crossed
    bool right_crossed = false;
    int left_sensors_crossed[3] = {0,0,0};
    bool left_crossed = start;
}

void Right_to_left::execute() {
    if (!left_crossed) {
        check_left_sensors();
    } else if (left_crossed && !right_crossed) {
        check_right_sensors();
    }
    correct_motor_speeds();
    if(left_crossed && right_crossed && (switch_states[0] || switch_states[2])){
        done = true;
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = 0;
        }
    }
}

void Right_to_left::check_left_sensors() {
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

void Right_to_left::check_right_sensors() {
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

void Right_to_left::correct_motor_speeds() {
    // 1. If neither the left or the right sensors have crossed, then set motor speeds to standard RTL speeds
    if (!left_crossed&&!right_crossed) {
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = stdMotorSpeedsRTL[i];
        }
    } 
    // // 2. If left sensors have crossed but the right have not yet, then set the motor speeds to standard RTL speeds
    else if (left_crossed && !right_crossed) {
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = stdMotorSpeedsRTL[i];
        }
    }

    // 3. If all right side sensors have crossed and left side sensors have crossed, slow motors down
    else if(right_crossed && left_crossed) {
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = slowMotorSpeedsRTL[i];
        }
    }

    // 4. if all the sensors have crossed and one of the counter detection switches was pressed set to 0 and finish
    else if((right_crossed && left_crossed)&&(switch_states[0]||switch_states[2])){
        for (int i = 0; i < 4; i++) {
            motorSpeeds[i] = slowMotorSpeedsRTL[i];
        }
        done = true;
        Serial3.println("RTL: DONE");
    }
}

Along_right_counter::Along_right_counter(bool forward, int tape_markings, bool on_end)
    :tape_markings(tape_markings), forward(forward), on_end(on_end){

    right_sensors_on[0] = 0; 
    right_sensors_on[1] = 0; 
    right_sensors_on[2] = 0; 

    right_sensors_num_crossed[0] = 0;
    right_sensors_num_crossed[1] = 0;
    right_sensors_num_crossed[2] = 0;
} 

void Along_right_counter::execute() {
    check_right_sensors();
    if (forward) { 
        if(!on_end){

            // 1. If foremost right sensor is on desired tape marking, stop motors
            if (right_sensors_num_crossed[2] == (tape_markings-1) && right_sensors_on[2] == 1) { 
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = 0; // slowMotorSpeedsForwardRightAC[i];
                }
                Serial3.println("Foremost sensor on tape");
            }

            // 2. If backmost right sensor is on desired tape marking, run motors in reverse slow
            else if (right_sensors_num_crossed[0] >= (tape_markings-1) && right_sensors_on[0] == 1) { 
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = slowMotorSpeedsBackwardRightAC[i];
                }
                Serial3.println("Backmost sensor on tape");
            }

            // 3. If middle sensor is on desired tape marking, stop motors
            else if (right_sensors_num_crossed[1] == (tape_markings-1) && right_sensors_on[1] == 1) { // TODO add more checks for the other motors to ensure final destination
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = 0;
                }
                // done = true; // TODO 
                Serial3.println("Middle sensor on tape");
            }

            // 4. If no sensor has crossed the last tape marking, set motor speeds to standard AC_RIGHT speeds
            else if (right_sensors_num_crossed[0] <= (tape_markings-1) &&
                right_sensors_num_crossed[1] <= (tape_markings-1) &&
                right_sensors_num_crossed[2] <= (tape_markings-1)) {
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = stdMotorSpeedsForwardRightAC[i];
                }
                Serial3.println("No sensors crossed");
            }
        }else{

        }
\
        // Handle switches
        if(switch_states[0]&&switch_states[2]){
            // change nothing from previous logic
        }else if (switch_states[0]){
            // front switch has come off from the counter -> slow down inside motors(left)
            motorSpeeds[0] = 0.9 * motorSpeeds[0];
            motorSpeeds[2] = 0.9 * motorSpeeds[2];
        }else if (switch_states[2]){
            // back switch has come off from the vounter -> slow down outside motors(right)
            motorSpeeds[1] = 0.9 * motorSpeeds[1];
            motorSpeeds[3] = 0.9 * motorSpeeds[3];
        }else{
            // boths switches have come off counter
            for (int i = 0; i < 4; i++){
                motorSpeeds[i] = slowMotorSpeedsRTL[i];
            }
        }
    } else { // BACKWWARD
        if(!on_end){
                // 1. If no sensor has crossed the last tape marking, set motor speeds to standard AC_RIGHT_BACKWARD speeds
            if (right_sensors_num_crossed[0] < (tape_markings-1) &&
                right_sensors_num_crossed[1] < (tape_markings-1) &&
                right_sensors_num_crossed[2] < (tape_markings-1)) {
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = stdMotorSpeedsBackwardRightAC[i];
                }
            }

            // 2. If backmost right sensor is on desired tape marking, slow motors
            if (right_sensors_num_crossed[0] == (tape_markings-1) && right_sensors_on[0] == 1) { // TODO CHECK!!! -- used to be 'or crossed' --right_sensors_num_crossed[0] == tape_markings ||
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = slowMotorSpeedsBackwardRightAC[i];
                }
            }

            // 3. If middle sensor has crossed last tape marking and is on tape, arrived where wanted
            if (right_sensors_num_crossed[1] >= (tape_markings-1) && right_sensors_on[1] == 1) { 
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = 0;
                }
                done = true; // TODO 
            }

            // 4. If frontmost sensor is on desired tape marker, go in reverse slowly
            if (right_sensors_num_crossed[2] >= (tape_markings-1) && right_sensors_on[2] == 1) { 
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = slowMotorSpeedsForwardRightAC[i];
                }
            }
        }
        else{
            Serial3.println("ARC_on_end_backward");
            if(right_sensors_num_crossed[0]< tape_markings-1){
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = stdMotorSpeedsBackwardRightAC[i];
                }
            }
            else if(right_sensors_num_crossed[0]== tape_markings-1){
                Serial3.println("going slow");
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = slowMotorSpeedsBackwardRightAC[i];
                }
            }
            else if(right_sensors_num_crossed[0]== tape_markings){
                for (int i = 0; i < 4; i++) {
                    motorSpeeds[i] = 0;
                }
                Serial3.println("done ARC");
                done = true;
            }
        }
        // Handle switches
        if(switch_states[0]&&switch_states[2]){
            // change nothing from previous logic
        }else if (switch_states[0]){
            // front switch has come off from the counter -> slow down inside motors(left)
            motorSpeeds[1] = 0.9 * motorSpeeds[1];
            motorSpeeds[3] = 0.9 * motorSpeeds[3];
        }else if (switch_states[2]){
            // back switch has come off from the vounter -> slow down outside motors(right)
            motorSpeeds[0] = 0.9 * motorSpeeds[0];
            motorSpeeds[2] = 0.9 * motorSpeeds[2];
        }else{
            // for (int i = 0; i < 4; i++){
            //     motorSpeeds[i] = slowMotorSpeedsRTL[i];
            // }
        }
    }
}

void Along_right_counter::check_right_sensors() {
    for (int i = 0; i < 3; i++) {
        bool on = analogRead(sensor_pins_right[i]) > Reflectance_threshold;
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


/*
LEFT COUNTER
*/

Along_left_counter::Along_left_counter(bool forward, int tape_markings, bool on_end)
    :tape_markings(tape_markings), forward(forward), on_end(on_end){

    left_sensors_on[0] = 0; 
    left_sensors_on[1] = 0; 
    left_sensors_on[2] = 0; 

    left_sensors_num_crossed[0] = 0;
    left_sensors_num_crossed[1] = 0;
    left_sensors_num_crossed[2] = 0;
}

void Along_left_counter::execute() {

    check_left_sensors();

    Serial3.println("LEFT SENSORS: " + String(analogRead(sensor_pins_left[0])) + " " + String(analogRead(sensor_pins_left[1])) + " " + String(analogRead(sensor_pins_left[2])));
    // Serial3.println("RIGHT SENSORS: " + String(analogRead(sensor_pins_right[0])) + " " + String(analogRead(sensor_pins_right[1])) + " " + String(analogRead(sensor_pins_right[2])));

    // Serial3.println("Sensors on: back: " + String(left_sensors_on[0]) + " middle: " + String(left_sensors_on[1]) + " front: " + String(left_sensors_on[2]));
    // Serial3.println("Sensors crossed: back: " + String(left_sensors_num_crossed[0]) + " middle: " + String(left_sensors_num_crossed[1]) + " front: " + String(left_sensors_num_crossed[2]));
    
    if (forward) {

        // 1. If foremost right sensor is on desired tape marking, run motors in reverse to stop
        if (left_sensors_num_crossed[2] >= (tape_markings-1) && left_sensors_on[2] == 1) { 
            for (int i = 0; i < 4; i++) {
                motorSpeeds[i] =stdMotorSpeedsBackwardLeftAC[i]; //stdMotorSpeedsBackward[i];
            }
            Serial3.println("Frontmost sensor on tape");
        }

        // 2. If middle sensor is on desired tape marking, stop motors
        else if (left_sensors_num_crossed[1] >= (tape_markings-1) && left_sensors_on[1] == 1) {
            for (int i = 0; i < 4; i++) {
                motorSpeeds[i] = 0;
            }
            Serial3.println("Middle sensor on tape");
            // done = true; // TODO 
        } 

        // 3. If middle sensor has over exceeded desired tape marking, go slowly in reverse
        else if (left_sensors_num_crossed[1] == tape_markings) {
            for (int i = 0; i < 4; i++) {
                motorSpeeds[i] =  slowMotorSpeedsBackwardLeftAC[i]; // slowMotorSpeedsBackward[i];
            }
            Serial3.println("Middle sensor crossed tape. Reverse");
        }


        // // 4. If backmost sensor is on desired tape marking, go slowly in reverse -- SHOULD BE UNNECESSARY
        // else if (left_sensors_num_crossed[0] >= (tape_markings-1) && left_sensors_on[0] == 1) { 
        //     for (int i = 0; i < 4; i++) {
        //         motorSpeeds[i] = slowMotorSpeedsBackwardLeftAC[i];
        //     }
        //     Serial3.println("Backmost sensor on tape");
        // }

        // // 5. If backmost sensor has crossed desired tape marking, go slowly in reverse -- SHOULD BE UNNECESSARY
        // else if (left_sensors_num_crossed[0] >= tape_markings) {
        //     for (int i = 0; i < 4; i++) {
        //         motorSpeeds[i] = slowMotorSpeedsBackwardLeftAC[i];
        //     }
        //     Serial3.println("Backmost sensor crossed tape. Reverse");
        // }

        // 6. If no sensor has crossed the last tape marking, set motor speeds to standard AC_LEFT speeds
        else if (left_sensors_num_crossed[0] <= (tape_markings-1) &&
            left_sensors_num_crossed[1] <= (tape_markings-1) &&
            left_sensors_num_crossed[2] <= (tape_markings-1)) {
            for (int i = 0; i < 4; i++) {
                motorSpeeds[i] = stdMotorSpeedsForward[i]; //stdMotorSpeedsForwardLeftAC[i];
            }
            Serial3.println("Straight ahead matey!");
        }

        // if(switch_states[1]&&switch_states[3]){
        //     // change nothing from previous logic
        // }
        // else if (switch_states[1])
        // {
        //     // front switch has come off from the counter -> slow down inside motors(left)
        //     motorSpeeds[1] = 0.9 * motorSpeeds[1];
        //     motorSpeeds[3] = 0.9 * motorSpeeds[3];
        // }
        // else if (switch_states[3])
        // {
        //     // back switch has come off from the vounter -> slow down outside motors(right)
        //     motorSpeeds[0] = 0.9 * motorSpeeds[0];
        //     motorSpeeds[2] = 0.9 * motorSpeeds[2];
        // }
        // else
        // {
        //     for (int i = 0; i < 4; i++)
        //     {
        //         motorSpeeds[i] = slowMotorSpeedsLTR[i];
        //     }
        // }
    } 
    //  else {
    //     // 1. If no sensor has crossed the last tape marking, set motor speeds to standard AC_RIGHT speeds
    //     if (left_sensors_num_crossed[0] < (tape_markings-1) &&
    //         left_sensors_num_crossed[1] < (tape_markings-1) &&
    //         left_sensors_num_crossed[2] < (tape_markings-1)) {
    //         for (int i = 0; i < 4; i++) {
    //             motorSpeeds[i] = stdMotorSpeedsBackwardRightAC[i];
    //         }
    //     }

    //     // 2. If backmost right sensor has crossed desired tape marking or is on it, slow motors
    //     if (left_sensors_num_crossed[0] == tape_markings ||
    //         (left_sensors_num_crossed[0] == (tape_markings-1) && left_sensors_on[0] == 1)) { // TODO TODO!!! TODO!!! check w/ benedikt if this is forward sensor and if tape_markings - 1 is correct
    //         for (int i = 0; i < 4; i++) {
    //             motorSpeeds[i] = slowMotorSpeedsBackwardRightAC[i];
    //         }
    //     }

    //     // 3. If middle sensor has crossed last tape marking and is on tape, arrived where wanted
    //     if (left_sensors_num_crossed[1] == (tape_markings-1) && left_sensors_on[1] == 1) { // TODO add more checks for the other motors to ensure final destination
    //         for (int i = 0; i < 4; i++) {
    //             motorSpeeds[i] = 0;
    //         }
    //         done = true; // TODO instead, do fine adjustments to actually center on tape, otherwise why 3 sensors smh
    //     }

    //     // 4. If middle sensor has crossed desired tape marking, go in reverse slowly until on tape marking
    //     // TODO

    //     if(switch_states[1]&&switch_states[3]){
    //         // change nothing from previous logic
    //     }
    //     else if (switch_states[1])
    //     {
    //         // front switch has come off from the counter -> slow down inside motors(left)
    //         motorSpeeds[0] = 0.9 * motorSpeeds[0];
    //         motorSpeeds[2] = 0.9 * motorSpeeds[2];
    //     }
    //     else if (switch_states[3])
    //     {
    //         // back switch has come off from the vounter -> slow down outside motors(right)
    //         motorSpeeds[1] = 0.9 * motorSpeeds[1];
    //         motorSpeeds[3] = 0.9 * motorSpeeds[3];
    //     }
    //     else
    //     {
    //         for (int i = 0; i < 4; i++)
    //         {
    //             motorSpeeds[i] = slowMotorSpeedsLTR[i];
    //         }
    //     }
    // }
}

void Along_left_counter::check_left_sensors() {
    for (int i = 0; i < 3; i++) {
        bool on = analogRead(sensor_pins_left[i]) >= Reflectance_threshold;
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

Move::Move(int inches, bool along_right, bool along_left, bool forward)
    :inches(inches), along_right_counter(along_right), along_left_counter(along_left), forward(forward), started(false){
    start_time = 0;
}

void Move::execute(){
    
    Serial3.println("MOVE");

    if(!started){
        start_time = millis();
        started = true;
        Serial3.println(start_time);
    }
    if((millis())>start_time+100*inches){
        this->done = true;
        Serial3.println("MOVE: DONE");
        for (int i = 0; i <= 3; i++) {
            if(forward){
                motorSpeeds[i] = stdMotorSpeedsBackward[i];
            }else{
                motorSpeeds[i] = stdMotorSpeedsForward[i];
            }
        }
        delay(15);
        for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = 0;
        }
    }else if(along_left_counter){
        if(forward){
            for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = stdMotorSpeedsForwardLeftAC[i];
            }
        }else{
            for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = stdMotorSpeedsBackwardLeftAC[i];
            }
        }
    }else if(along_right_counter){
        if(forward){
            for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = stdMotorSpeedsForwardRightAC[i];
            }
        }else{
            for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = stdMotorSpeedsBackwardRightAC[i];
            }
        }
    }else{
        if(forward){
            for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = stdMotorSpeedsForward[i];
            }
        }else{
            for (int i = 0; i <= 3; i++) {
                motorSpeeds[i] = stdMotorSpeedsBackward[i];
            }
        }
    }
}