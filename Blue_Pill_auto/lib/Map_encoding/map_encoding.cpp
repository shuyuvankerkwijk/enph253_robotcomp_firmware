#include "map_encoding.h"
#include "globals.h"
#include <iostream>
#include <vector>
#include <memory>

// Constructor for Path
Path::Path(String start, String end)
    : done(false) {
    if (start.equalsIgnoreCase("Start")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Move up 1s, move to right counter, move slow down along right counter
            moves_series[0] = new Move(5, false, false); 
            moves_series[1] = new Left_to_right(true);
            moves_series[2] = new Along_right_counter(false, 1, true);
        } else if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Start to Tomato
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Start to Cutting
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Define moves for Start to Serving_area
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Start to Cooktop
        } else if (end.equalsIgnoreCase("Plates")) {
            // Move up 1s, move to left counter, move along counter passing 2 markings fast, slow to the next marking
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Start to Lettuce
        }
    } else if (start.equalsIgnoreCase("Cheese")) {
        if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Cheese to Tomato
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Cheese to Cutting
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Define moves for Cheese to Serving_area
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Cheese to Cooktop
        } else if (end.equalsIgnoreCase("Plates")) {
            // Move up 1s along right counter, move to left counter, move along counter passing 2 markings fast, slow to the next marking
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Cheese to Lettuce
        }
    } else if (start.equalsIgnoreCase("Tomato")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Define moves for Tomato to Cheese
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Tomato to Cutting
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Define moves for Tomato to Serving_area
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Tomato to Cooktop
        } else if (end.equalsIgnoreCase("Plates")) {
            // Define moves for Tomato to Plates
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Tomato to Lettuce
        }
    } else if (start.equalsIgnoreCase("Cutting")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Define moves for Cutting to Cheese
        } else if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Cutting to Tomato
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Define moves for Cutting to Serving_area
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Cutting to Cooktop
        } else if (end.equalsIgnoreCase("Plates")) {
            // Define moves for Cutting to Plates
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Cutting to Lettuce
        }
    } else if (start.equalsIgnoreCase("Serving_area")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Define moves for Serving_area to Cheese
        } else if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Serving_area to Tomato
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Serving_area to Cutting
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Serving_area to Cooktop
        } else if (end.equalsIgnoreCase("Plates")) {
            // Define moves for Serving_area to Plates
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Serving_area to Lettuce
        }
    } else if (start.equalsIgnoreCase("Cooktop")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Define moves for Cooktop to Cheese
        } else if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Cooktop to Tomato
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Cooktop to Cutting
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Define moves for Cooktop to Serving_area
        } else if (end.equalsIgnoreCase("Plates")) {
            // Define moves for Cooktop to Plates
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Cooktop to Lettuce
        }
    } else if (start.equalsIgnoreCase("Plates")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Define moves for Plates to Cheese
        } else if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Plates to Tomato
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Plates to Cutting
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Move down 1 marking fast, from left counter to right counter, search for beacon()
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Plates to Cooktop
        } else if (end.equalsIgnoreCase("Lettuce")) {
            // Define moves for Plates to Lettuce
        }
    } else if (start.equalsIgnoreCase("Lettuce")) {
        if (end.equalsIgnoreCase("Cheese")) {
            // Define moves for Lettuce to Cheese
        } else if (end.equalsIgnoreCase("Tomato")) {
            // Define moves for Lettuce to Tomato
        } else if (end.equalsIgnoreCase("Cutting")) {
            // Define moves for Lettuce to Cutting
        } else if (end.equalsIgnoreCase("Serving_area")) {
            // Define moves for Lettuce to Serving_area
        } else if (end.equalsIgnoreCase("Cooktop")) {
            // Define moves for Lettuce to Cooktop
        } else if (end.equalsIgnoreCase("Plates")) {
            // Define moves for Lettuce to Plates
        }
    }
}

// Destructor for Path to clean up dynamically allocated memory
Path::~Path() {
    for (int i = 0; i < 6; ++i) {
        delete moves_series[i];
    }
}

void Path::execute() {
    bool is_done = true;
    for (int i = 0; i < 6; ++i) {
        if (moves_series[i] != nullptr && !moves_series[i]->done) {
            is_done = false;
            moves_series[i]->execute();
            break; // Execute only the first move that is not done
        }
    }

    done = is_done;
    
}
