#include "map_encoding.h"
#include "globals.h"


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


// Calculate path method for Position class
Path* Path::calculate_path(String start, String end) const {
    if(start.equalsIgnoreCase("Start")){
        if(end.equalsIgnoreCase("Cheese")){
            //move up 1s, move to right counter, move slow down along right counter
            return new Path(true, false, false, 1, 6, true);
        }else if(end.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            //move up 1s, move to left counter, move along counter passing 2 markings fast, slow to the next marking
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    else if(this->name.equalsIgnoreCase("Cheese")){
        if(end->name.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            // move up 1s along right counter, move to left counter, move along counter passing 2 markings fast, slow to the next marking
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    }else if(this->name.equalsIgnoreCase("Tomato")){
        if(end->name.equalsIgnoreCase("Cheese")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    }else if(this->name.equalsIgnoreCase("Cutting")){
        if(end->name.equalsIgnoreCase("Cheese")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    }else if(this->name.equalsIgnoreCase("Serving_area")){
        if(end->name.equalsIgnoreCase("Cheese")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    }else if(this->name.equalsIgnoreCase("Cooktop")){
        if(end->name.equalsIgnoreCase("Cheese")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    }else if(this->name.equalsIgnoreCase("Plates")){
        if(end->name.equalsIgnoreCase("Cheese")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            // move down 1 marking fast, from left counter to right counter, search for beacong()
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Lettuce")){
            return new Path(true, false, false, 1, 6, true);
        }
    }else if(this->name.equalsIgnoreCase("Lettuce")){
        if(end->name.equalsIgnoreCase("Cheese")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Tomato")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cutting")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Serving_area")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Cooktop")){
            return new Path(true, false, false, 1, 6, true);
        }else if(end->name.equalsIgnoreCase("Plates")){
            return new Path(true, false, false, 1, 6, true);
        }
    }
    return nullptr;
    }
}

void Path::execute() {
    if (left_to_right && !ltr_obj.done) {
        ltr_obj.run_cycle();
    } else if (right_to_left && !rtl_obj.done) {
        rtl_obj.run_cycle();
    } else if (find_beacon) {
        // Handle IR beacon finding logic
        //TODO by Kamyar
    } else if (!ac_obj.done) {
        ac_obj.run_cycle();
    }else{
        done = true;
        current = goal;
    }
}
