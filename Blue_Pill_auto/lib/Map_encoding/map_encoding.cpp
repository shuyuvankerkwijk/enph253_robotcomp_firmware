#include "map_encoding.h"

// Position constructor
Position::Position(String name, Counter side, int tape_count, int y_position, Mark mark)
    : name(name), side(side), tape_count(tape_count), y_position(y_position), mark(mark) {
    // Initialization code if needed
}

// Path constructor
Path::Path(bool left_to_right, bool right_to_left, bool find_beacon, int tape_count, bool done)
    : left_to_right(left_to_right), right_to_left(right_to_left), find_beacon(find_beacon), done(done) {
    // Initialization code if needed
}

bool Position::equals(Position* goal) const {
    return this->name.equals(goal->name);
}

// Calculate path method for Position class
Path* Position::calculate_path(Position* end) const {
    bool left_to_right = (this->side == left && end->side == right);
    bool right_to_left = (this->side == right && end->side == left);
    bool find_beacon = (end->mark == IR_beacon);
    int inches_to_travel = end->y_position - this->y_position;

    return new Path(left_to_right, right_to_left, find_beacon, tape_count, false);
}

void Path::execute() {
    if (left_to_right && !ltr_obj.done) {
        ltr_obj.run_cycle();
    } else if (right_to_left && !rtl_obj.done) {
        rtl_obj.run_cycle();
    } else if (find_beacon) {
        // Handle IR beacon finding logic
    } else if (!ac_obj.done) {
        ac_obj.run_cycle();
    }
    done = true;
}
