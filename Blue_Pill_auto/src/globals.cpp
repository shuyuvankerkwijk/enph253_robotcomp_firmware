#include "globals.h"
#include "map_encoding.h"

int Reflectance_threshold = 450;
bool switch_states[4] = {false, false, false, false}; // is switch pressed or not -- switch is high when unpressed, low when pressed
/**
 * switch_states[0] = front left switch
 * switch_states[1] = front right switch
 * switch_states[2] = back left switch
 * switch_states[3] = back right switch
 * 
 * same for motors
 */

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

/**
 * Motor PWM duty cycles for 200 RPM at 16V & 100Hz
 * ß
 * Front motor by Kamyar calibration:
 * 
 * M    F       R
 * 0    200     195
 * 1    193     187
 * 2    148     143
 * 3    s     177
 */

int stdMotorSpeedsRTL[4] = {-195, 187, 143, -177}; 
int stdMotorSpeedsLTR[4] = {200, -187, -143, 180}; 
int stdMotorSpeedsForward[4] = {200, 193, 148, 180};
int stdMotorSpeedsBackward[4] = {-195, -187, -143, -177};

int stdMotorSpeedsForwardLeftAC[4] = {200, 193+20, 148, 180+20}; // set right wheels at 2% faster
int stdMotorSpeedsForwardRightAC[4] = {200+20, 193, 148+20, 180}; // set left wheels at 2% faster
int stdMotorSpeedsBackwardLeftAC[4] = {-195, -187-20, -143, -177-20}; // set right wheels at 2% faster
int stdMotorSpeedsBackwardRightAC[4] = {-195-20, -187, -143-20, -177}; // set left wheels at 2% faster

int slowMotorSpeedsRTL[4] = {-50, 50, 50, -50}; // TODO: change to correct values
int slowMotorSpeedsLTR[4] = {50, -50, -50, 50}; // TODO: change to correct values
int slowMotorSpeedsForward[4] = {50, 50, 50, 50}; // TODO: change to correct values
int slowMotorSpeedsBackward[4] = {-50, -50, -50, -50}; // TODO: change to correct values

int slowMotorSpeedsForwardLeftAC[4] = {50, 50+10, 50, 50+10}; // set right wheels at 1% faster
int slowMotorSpeedsForwardRightAC[4] = {50+10, 50, 50+10, 50}; // set left wheels at 1% faster
int slowMotorSpeedsBackwardLeftAC[4] = {-50, -50-10, -50, -50-10}; // set right wheels at 1% faster
int slowMotorSpeedBackwardRightAC[4] = {-50-10, -50, -50-10, -50}; // set left wheels at 1% faster

// PinName motor_pwm_pins[4] = {PB_8, PB_9, PB_6, PB_7}; // Not used anywhere, just for reference
// PinName motor_d_select_pins[4] = {PB_15, PB_14, PB_12, PB_13}; // Not used anywhere, just for reference

PinName sensor_pins_left[5] = {PA_0, PA_1, PA_2, PA_3, PA_4};
PinName sensor_pins_right[5] = {PA_5, PA_6, PA_7, PB_0, PB_1};

HardwareSerial Serial2(PB_11, PB_10); // RX, TX

bool run = false;

Position* current = &Start; 
Position* goal = &Start;
