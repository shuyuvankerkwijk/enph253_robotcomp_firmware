#include "globals.h"
#include "map_encoding.h"

int Reflectance_threshold = 450;
bool switch_states[4] = {false, false, false, false}; // is switch pressed or not -- switch is high when unpressed, low when pressed

// Front house robot positions
Position Start(String("Start"), right, 1, 6, tape); //TODO: should start on left (to grab plates)
Position Cheese(String("Cheese"), right, 1, 6, tape); // name, side, tape_count, y_position, mark
Position Tomato(String("Tomato"), left, 1, 6, tape);
Position Cutting(String("Cutting"), left, 2, 24, tape);
Position Serving_Area(String("Serving_area"), right, 1, 48, IR_beacon);
Position Cooktop(String("Cooktop"), left, 3, 72, tape);
Position Plates(String("Plates"), left, 3, 90, tape);
Position Lettuce(String("Lettuce"), right, 3, 90, tape);

int motorSpeeds[4] = {0, 0, 0, 0};

int stdMotorSpeedsRTL[4] = {100, 100, 100, 100}; // TODO: change to correct values
int stdMotorSpeedsLTR[4] = {100, 100, 100, 100}; // TODO: change to correct values
int stdMotorSpeedsAC[4] = {100, 100, 100, 100}; // TODO: change to correct values

int slowMotorSpeedsRTL[4] = {25, 25, 25, 25}; // TODO: change to correct values
int slowMotorSpeedsLTR[4] = {25, 25, 25, 25}; // TODO: change to correct values
int slowMotorSpeedsAC[4] = {25, 25, 25, 25}; // TODO: change to correct values


// PinName motor_pwm_pins[4] = {PB_8, PB_9, PB_6, PB_7}; // Not used anywhere, just for reference
// PinName motor_d_select_pins[4] = {PB_15, PB_14, PB_12, PB_13}; // Not used anywhere, just for reference

PinName sensor_pins_left[5] = {PA_0, PA_1, PA_2, PA_3, PA_4};
PinName sensor_pins_right[5] = {PA_5, PA_6, PA_7, PB_0, PB_1};

HardwareSerial Serial2(PB_11, PB_10); // RX, TX

bool run = false;

Position* current = &Start; 
Position* goal = &Start;
