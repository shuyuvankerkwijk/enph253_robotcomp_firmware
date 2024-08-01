#include "globals.h"
#include "map_encoding.h"

int Reflectance_threshold = 500;
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

int slowMotorSpeedsRTL[4] = {-195/2, 187/2, 143/2, -177/2}; // TODO: change to correct values
int slowMotorSpeedsLTR[4] = {200/2, -187/2, -143/2, 180/2}; // TODO: change to correct values
int slowMotorSpeedsForward[4] = {200/2, 193/2, 148/2, 180/2}; // TODO: change to correct values
int slowMotorSpeedsBackward[4] = {-195/2, -187/2, -143/2, -177/2}; // TODO: change to correct values

int slowMotorSpeedsForwardLeftAC[4] = {50, 50+10, 50, 50+10}; // set right wheels at 1% faster
int slowMotorSpeedsForwardRightAC[4] = {50+10, 50, 50+10, 50}; // set left wheels at 1% faster
int slowMotorSpeedsBackwardLeftAC[4] = {-50, -50-10, -50, -50-10}; // set right wheels at 1% faster
int slowMotorSpeedBackwardRightAC[4] = {-50-10, -50, -50-10, -50}; // set left wheels at 1% faster

// PinName motor_pwm_pins[4] = {PB_8, PB_9, PB_6, PB_7}; // Not used anywhere, just for reference
// PinName motor_d_select_pins[4] = {PB_15, PB_14, PB_12, PB_13}; // Not used anywhere, just for reference

PinName sensor_pins_left[5] = {PA_5, PA_4, PA_3}; // left front, middle, back #TODO: check!
PinName sensor_pins_right[5] = {PA_2, PA_1, PA_0}; // right front, middle, back


bool run = false;

Position* current = Positions; 
Position* goal = Positions;
