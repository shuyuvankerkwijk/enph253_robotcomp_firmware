#include "globals.h"
#include "map_encoding.h"

int Reflectance_threshold = 450;
bool switch_states[4] = {false, false, false, false};

// Front house robot positions
Position Start(String("Start"), right, 6, 1, tape);
Position Cheese(String("Cheese"), right, 6, 1, tape);
Position Tomato(String("Tomato"), left, 6, 1, tape);
Position Cutting(String("Cutting"), left, 24, 2, tape);
Position Serving_Area(String("Serving_area"), right, 48, 1, IR_beacon);
Position Cooktop(String("Cooktop"), left, 72, 3, tape);
Position Plates(String("Plates"), left, 90, 3, tape);
Position Lettuce(String("Lettuce"), right, 90, 3, tape);

int motorSpeeds[4] = {0, 0, 0, 0};

PinName sensor_pins_left[5] = {PA_0, PA_1, PA_2, PA_3, PA_4};
PinName sensor_pins_right[5] = {PA_5, PA_6, PA_7, PB_0, PB_1};

HardwareSerial Serial2(PB_11, PB_10); // RX, TX

bool run = false;

Position* current = &Start;
Position* goal = &Start;
