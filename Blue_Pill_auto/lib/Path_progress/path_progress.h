#ifndef PATH_PROGRESS_H
#define PATH_PROGRESS_H

#include "Arduino.h"

class Moves {
public:
    Moves() : done(false) {}
    virtual void execute();
    bool done;
};

class Left_to_right : public Moves {
public:
    Left_to_right(bool start);
    void execute() override;

    int right_sensors_crossed; // 0 is before, 1 is on, and 2 is crossed
    bool right_crossed;
    int left_sensors_crossed;
    bool left_crossed;

    void check_right_sensors();
    void check_left_sensors();
    void correct_motor_speeds();
};

class Right_to_left : public Moves {
public:
    Right_to_left(bool start);
    void execute() override;

    //now just reading middle sensor.
    int right_sensors_crossed; // 0 is before, 1 is on, and 2 is crossed
    bool right_crossed;
    int left_sensors_crossed;
    bool left_crossed;

    void check_right_sensors();
    void check_left_sensors();
    void correct_motor_speeds();
};

class Move : public Moves {
public:
    Move(int inches, bool along_right, bool along_left, bool forward);

    bool started;

    bool along_right_counter;
    bool along_left_counter;
    bool forward;

    int inches;
    unsigned long start_time;

    void execute() override;
};

class Along_right_counter : public Moves {
public:
    Along_right_counter(bool forward, int tape_markings, bool on_end);

    bool forward;
    bool on_end;

    int tape_markings;
    int done_count;

    int right_sensors_on[3]; // 0 is off tape, 1 is on tape
    int right_sensors_num_crossed[3]; // The number of tape markings crossed by the sensor

    void execute() override;
    void check_right_sensors();
};

class Along_left_counter : public Moves {
public:
    Along_left_counter(bool forward, int tape_markings, bool on_end);

    bool forward;
    bool on_end;

    int tape_markings;
    int done_count;

    int left_sensors_on[3]; // 0 is off tape, 1 is on tape
    int left_sensors_num_crossed[3]; // The number of tape markings crossed by the sensor

    void execute() override;
    void check_left_sensors();
};

#endif // PATH_PROGRESS_H
