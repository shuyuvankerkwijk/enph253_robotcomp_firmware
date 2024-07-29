#ifndef MAP_ENCODING_H
#define MAP_ENCODING_H

#include <Arduino.h>
#include <string.h>
#include "path_progress.h"

// Forward declaration of Path class
class Path;

enum Counter { left, right };
enum Mark { tape, IR_beacon };

class Position {
public:
    Position(String name, Counter side, int tape_count, int y_position, Mark mark);

    String name;
    Counter side;
    int tape_count;
    int y_position;
    Mark mark;
    Path* calculate_path(Position* end) const;
    bool equals(Position* goal) const;
};

class Path {
public:
    Path(bool left_to_right, bool right_to_left, bool find_beacon, int tape_count, int inches_to_travel);
    void execute();
    bool done;
    bool left_to_right;
    Left_to_right ltr_obj;
    bool right_to_left;
    Right_to_left rtl_obj;
    bool find_beacon;
    Along_counter ac_obj;
};

#endif // MAP_ENCODING_H
