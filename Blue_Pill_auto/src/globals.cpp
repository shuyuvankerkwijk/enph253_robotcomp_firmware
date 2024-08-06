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

// /**
//  * Motor PWM duty cycles for 200 RPM at 16V & 100Hz
//  * ß
//  * Front motor by Kamyar calibration:
//  * 
//  * M    F       R
//  * 0    200     195
//  * 1    193     187
//  * 2    148     143
//  * 3    s     177
//  */

PinName motor_pwm_pins[4] = {PB_9, PB_8, PB_6, PB_7}; // motor 1 (goes backward w low select), motor 0 (goes forward), motor 2 (goes forward), motor 3 (goes forward), motor 4 (goes forward)
int motor_pwm_pins_ints[4] = {PB8, PB9, PB6, PB7}; 
int motor_d_select_pins[4] = {PB5, PB4, PA15, PB3};
int switch_pins[4] = {PB13, PB15, PB14, PB12}; // same as switch states
int sensor_pins_left[3] = {PA2, PA1, PA0}; // left back, middle, front
int sensor_pins_right[3] = {PA5, PA4, PA3}; // right back, middle, front

int stdMotorSpeedsRTL[4] = {int((-195-10)*2.5), int((187)*2.5), int((143+150)*2.5), int((-177)*2.5)}; 
int stdMotorSpeedsLTR[4] = {(200)*2, (-187)*2, (-143 - 20)*2, (180)*2};  // 0, 1, 2, 3
int stdMotorSpeedsForward[4] = {200*2, 193*2, 148*2, 180*2};
int stdMotorSpeedsBackward[4] = {-195, -187, -143, -177};

int stdMotorSpeedsForwardLeftAC[4] = {int(200*1.5), int((193+10)*1.5), int(148*1.5), int((180+10)*1.5)}; // set right wheels at 2% faster
int stdMotorSpeedsForwardRightAC[4] = {(200+20)*2, 193*2, (148+20)*2, 180*2}; // set left wheels at 2% faster
int stdMotorSpeedsBackwardLeftAC[4] = {-195*2, (-187-20)*2, -143*2, (-177-20)*2}; // set right wheels at 2% faster
int stdMotorSpeedsBackwardRightAC[4] = {(-195-20)*2, -187*2, (-143-20)*2, -177*2}; // set left wheels at 2% faster

int slowMotorSpeedsRTL[4] = {int(-195/1.3), int(187/1.3), int(143/1.3), int(-177/1.3)}; // TODO: change to correct values
int slowMotorSpeedsLTR[4] = {200*3, -187*3, -143*3, 180*3}; // TODO: change to correct values
int slowMotorSpeedsForward[4] = {200/2, 193/2, 148/2, 180/2}; // TODO: change to correct values
int slowMotorSpeedsBackward[4] = {int(-195/1), int(-187/1), int(-143/1), int(-177/1)}; // TODO: change to correct values

int slowMotorSpeedsForwardLeftAC[4] = {200, (193+20), 148, (180+20)}; // set right wheels at 1% faster
int slowMotorSpeedsForwardRightAC[4] = {(200+20), 193, (148+20), 180}; // set left wheels at 1% faster
int slowMotorSpeedsBackwardLeftAC[4] = {int(-195/1.2), int((-187-10)/1.2), int(-143/1.2), int((-177-10)/1.2)}; // set right wheels at 1% faster
int slowMotorSpeedsBackwardRightAC[4] = {(-195-20), -187, (-143-20), -177}; // set left wheels at 1% faster



bool run = true;

String begin_move = "Start";
String end_move = "Start";

