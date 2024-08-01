#include "map_encoding.h"
#include "globals.h"
#include <iostream>
#include <vector>
#include <memory>

// Calculate path method for Position class
Path::Path(String start, String end)
    : done(false) {
    if(start.equalsIgnoreCase("Start")){
        if(end.equalsIgnoreCase("Cheese")){
            //move up 1s, move to right counter, move slow down along right counter
            move_series.push_back(std::make_unique<Move>(5,false, false));
            move_series.push_back(std::make_unique<Left_to_right>(false));
            move_series.push_back(std::make_unique<Along_right_counter>(false, 1, true));
        }else if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Serving_area")){
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Plates")){
            //move up 1s, move to left counter, move along counter passing 2 markings fast, slow to the next marking
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    else if(start.equalsIgnoreCase("Cheese")){
        if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Serving_area")){
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Plates")){
            // move up 1s along right counter, move to left counter, move along counter passing 2 markings fast, slow to the next marking
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    }else if(start.equalsIgnoreCase("Tomato")){
        if(end.equalsIgnoreCase("Cheese")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Serving_area")){
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Plates")){
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    }else if(start.equalsIgnoreCase("Cutting")){
        if(end.equalsIgnoreCase("Cheese")){
        }else if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Serving_area")){
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Plates")){
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    }else if(start.equalsIgnoreCase("Serving_area")){
        if(end.equalsIgnoreCase("Cheese")){
        }else if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Plates")){
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    }else if(start.equalsIgnoreCase("Cooktop")){
        if(end.equalsIgnoreCase("Cheese")){
        }else if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Serving_area")){
        }else if(end.equalsIgnoreCase("Plates")){
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    }else if(start.equalsIgnoreCase("Plates")){
        if(end.equalsIgnoreCase("Cheese")){
        }else if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Serving_area")){
            // move down 1 marking fast, from left counter to right counter, search for beacong()
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Lettuce")){
        }
    }else if(start.equalsIgnoreCase("Lettuce")){
        if(end.equalsIgnoreCase("Cheese")){
        }else if(end.equalsIgnoreCase("Tomato")){
        }else if(end.equalsIgnoreCase("Cutting")){
        }else if(end.equalsIgnoreCase("Serving_area")){
        }else if(end.equalsIgnoreCase("Cooktop")){
        }else if(end.equalsIgnoreCase("Plates")){
        }
    }
}

void Path::execute() {
    for (const auto& move : move_series) {
        if (!move->done) {
            move->execute();
            break; // Execute only the first move that is not done
        }
    }
}