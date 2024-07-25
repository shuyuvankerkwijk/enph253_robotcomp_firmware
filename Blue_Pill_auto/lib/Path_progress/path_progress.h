#ifndef PATH_PROGRESS_H
#define PATH_PROGRESS_H

class Left_to_right {
public:
    Left_to_right();
    bool done;

    // int std_motor_speeds[4];

    int right_sensors_crossed[3]; // 0 is before, 1 is on, and 2 is crossed
    bool right_crossed;
    int left_sensors_crossed[3];
    bool left_crossed;

    void run_cycle();
    void check_right_sensors();
    void check_left_sensors();
    void correct_motor_speeds();
};

class Right_to_left {
public:
    Right_to_left();
    bool done;

    // int std_motor_speeds[4];

    int right_sensors_crossed[3]; // 0 is before, 1 is on, and 2 is crossed
    bool right_crossed;
    int left_sensors_crossed[3];
    bool left_crossed;

    void run_cycle();
    void check_right_sensors();
    void check_left_sensors();
    void correct_motor_speeds();
};

class Along_counter {
public:
    Along_counter();

    bool done;

    // int std_motor_speeds[4];

    bool forward;
    bool backward;
    int inches;
    int tape_markings;

    bool ac_left; // needed? -- shuyu addition
    bool ac_right;

    int right_sensors_on[3]; // 0 is off tape, 1 is on tape
    int left_sensors_on[3];

    int right_sensors_num_crossed[3]; // The number of tape markings crossed by the sensor
    int left_sensors_num_crossed[3]; 

    void run_cycle();
    void check_right_sensors();
    void check_left_sensors();
    void correct_motor_speeds();
};

#endif // PATH_PROGRESS_H
