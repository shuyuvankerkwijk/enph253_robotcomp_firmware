#include "map_encoding.h"

// Position constructor
Position::Position(String name, Counter side, int tape_count, int y_position, Mark mark)
    : name(name), side(side), tape_count(tape_count), y_position(y_position), mark(mark) {
    // Initialization code if needed
}

// Path constructor
Path::Path(bool left_to_right, bool right_to_left, bool find_beacon, int tape_count, int inches_to_travel, bool along_right)
    : left_to_right(left_to_right), right_to_left(right_to_left), find_beacon(find_beacon), done(done) {
    
    if (left_to_right) {
        ltr_obj = Left_to_right();
    } else if (right_to_left) {
        rtl_obj = Right_to_left();
    } else if (find_beacon) {
        // Handle IR beacon finding logic
    }
    ac_obj = Along_counter();
    
}

// Equals method for Position class
bool Position::equals(Position* goal) const {
    return this->name.equals(goal->name);
}

// Calculate path method for Position class
Path* Position::calculate_path(Position* end) const {
    bool left_to_right = (this->side == left && end->side == right); // need to cross to right counter?
    bool right_to_left = (this->side == right && end->side == left); // need to cross to left counter?
    bool find_beacon = (end->mark == IR_beacon);
    int inches_to_travel = end->y_position - this->y_position;

    bool along_right = (end->side==right);
    Path* result = new Path(left_to_right, right_to_left, find_beacon, tape_count, inches_to_travel, along_right);

    //define the counter side we are going on
    if(end->side == right){
        result->ac_obj.ac_right=true;
        result->ac_obj.ac_right=false;
    }else if(end->side == left){
        result->ac_obj.ac_right=false;
        result->ac_obj.ac_right=true;
    }

    //define if we are going forward or backwards
    if(inches_to_travel>0){
        result->ac_obj.forward=true;
        result->ac_obj.backward=false;
    }else if(inches_to_travel<=0){
        result->ac_obj.forward=false;
        result->ac_obj.backward=true;
    }

    //going to a side from the middle start position.
    if(this->name.equals("start")){
        if(result->left_to_right == true){
            result->ltr_obj.right_crossed=true;
        }else if(result->right_to_left==true){
            result->rtl_obj.left_crossed = true;
        }

        result->ac_obj.tape_markings = tape_count;
    }

    return result;
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
    }else{
        done = true;
    }
}
