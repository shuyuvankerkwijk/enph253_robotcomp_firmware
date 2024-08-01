#ifndef MAP_ENCODING_H
#define MAP_ENCODING_H

#include <Arduino.h>
#include <string.h>
#include "path_progress.h"

// Forward declaration of Path class
class Path;

class Path {
public:
    Path(bool left_to_right, bool right_to_left, bool find_beacon, int tape_count, int inches_to_travel, bool along_right);
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
