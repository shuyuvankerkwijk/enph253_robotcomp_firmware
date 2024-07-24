#include "path_progress.h"
#include "globals.h"

void Left_to_right::run_cycle() {
    if (!right_corssed) {
        check_right_sensors();
    } else if (right_corssed) {
        // Additional logic for when the right side is crossed
    }
}

void Left_to_right::check_left_sensors() {
    // Implement sensor checking logic
}

void Left_to_right::check_right_sensors() {
    // Implement sensor checking logic
}

void Left_to_right::correct_motor_speeds() {
    // Implement motor speed correction logic
}

void Right_to_left::run_cycle() {
    if (!left_crossed) {
        check_left_sensors();
    } else if (left_crossed) {
        // Additional logic for when the left side is crossed
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
        // Implement forward movement logic
    } else if (backward) {
        // Implement backward movement logic
    }
}

void Along_counter::check_left_sensors() {
    // Implement sensor checking logic
}

void Along_counter::check_right_sensors() {
    // Implement sensor checking logic
}

void Along_counter::correct_motor_speeds() {
    // Implement motor speed correction logic
}
