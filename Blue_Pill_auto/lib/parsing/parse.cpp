
#include "parse.h"
#include "globals.h"
#include "map_encoding.h"
/**
 * this parses all of the incoming serial data
 * change of variables, etc...
 * 
 */

/**
 * Position Positions[8] = {
    Position(String("Start"), right, 1, 6, tape), 
    Position(String("Cheese"), right, 1, 6, tape), 
    Position(String("Tomato"), left, 1, 6, tape),
    Position(String("Cutting"), left, 2, 24, tape),
    Position(String("Serving_area"), right, 1, 48, IR_beacon),
    Position(String("Cooktop"), left, 3, 72, tape),
    Position(String("Plates"), left, 3, 90, tape),
    Position(String("Lettuce"), right, 3, 90, tape)
};
Position* goal;
 */

String parse(String message) { //TODO
    if(message.equalsIgnoreCase("run")){
        run = true;
        return "BP recieved: run";
    }else if(message.equalsIgnoreCase("stop")){
        run = false;
        return "BP recieved: stop";
    }else if(message.substring(0,5).equalsIgnoreCase("GOTO:")){
        // RK. De-reference objects at index in array to get ptr instead.
        if(message.substring(5).equalsIgnoreCase("Cheese")){
            goal = Positions + sizeof(Position);
            return "BP recieved: GOTO:Cheese";
        }else if(message.substring(5).equalsIgnoreCase("Tomato")){
            goal = Positions + 2*sizeof(Position);
            return "BP recieved: GOTO:Tomato";
        }else if(message.substring(5).equalsIgnoreCase("Cutting")){
            goal = Positions + 3*sizeof(Position);
            return "BP recieved: GOTO:Cutting";
        }else if(message.substring(5).equalsIgnoreCase("Serving_area")){
            goal = Positions + 4*sizeof(Position);
            return "BP recieved: GOTO:Serving_area";
        }else if(message.substring(5).equalsIgnoreCase("Cooktop")){
            goal = Positions + 5*sizeof(Position);
            return "BP recieved: GOTO:Cooktop";
        }else if(message.substring(5).equalsIgnoreCase("Plates")){
            goal = Positions + 6*sizeof(Position);
            return "BP recieved: GOTO:Plates";
        }else if(message.substring(5).equalsIgnoreCase("Lettuce")){
            goal = Positions + 7*sizeof(Position);
            return "BP recieved: GOTO:Lettuce";
        }
    }
    else if(message.substring(0,4).equalsIgnoreCase("move")){

    }
    else if(message.substring(0,4).equalsIgnoreCase("ISAT")){
        if(message.substring(4).equalsIgnoreCase("Start")){
            current = Positions;
            return "BP recieved: ISAT:Cheese";
        }else if(message.substring(4).equalsIgnoreCase("Cheese")){
            current = Positions + sizeof(Position);
            return "BP recieved: ISAT:Cheese";
        }else if(message.substring(4).equalsIgnoreCase("Tomato")){
            current = Positions + 2*sizeof(Position);
            return "BP recieved: ISAT:Tomato";
        }else if(message.substring(4).equalsIgnoreCase("Cutting")){
            current = Positions + 3*sizeof(Position);
            return "BP recieved: ISAT:Cutting";
        }else if(message.substring(4).equalsIgnoreCase("Serving_area")){
            current = Positions + 4*sizeof(Position);
            return "BP recieved: ISAT:Serving_area";
        }else if(message.substring(4).equalsIgnoreCase("Cooktop")){
            current = Positions + 5*sizeof(Position);
            return "BP recieved: ISAT:Cooktop";
        }else if(message.substring(4).equalsIgnoreCase("Plates")){
            current = Positions + 6*sizeof(Position);
            return "BP recieved: ISAT:Plates";
        }else if(message.substring(4).equalsIgnoreCase("Lettuce")){
            current = Positions + 7*sizeof(Position);
            return "BP recieved: ISAT:Lettuce";
        }
    }
    return "";
}
