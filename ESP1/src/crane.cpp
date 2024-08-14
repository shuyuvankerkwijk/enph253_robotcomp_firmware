#include <Arduino.h>
#include "driver/ledc.h"
#include "crane.h"
#include "pinout.h"
// #include "ws.h"

int CranePWMFreq = 1000;  // PWM frequency in Hz 
int CranePWMResolution = 8;  // PWM resolution in bits

int craneRChannelExtendB = 0;  
int craneRChannelRetractB = 1;  

// BACK ARM VARIABLES
volatile int encoderPosZB = 0; // global position of encoder, starts at 0
volatile int directionZB = 0; // 0 is nothing, 1 is clockwise, -1 is counter-clockwise

volatile int encoderPosRB = -5; // global position of encoder, starts at -5 because first extension is until it hits switch
volatile int directionRB = 0; // 0 is nothing, 1 is forward, -1 is backward

volatile int posYB = -1;// -1 is up (retracted), 1 is down (extended), starts retracted

// BACK ARM
void handleZEncoderB() {
    // Check the direction of rotation 
    if (directionZB == -1) {
        encoderPosZB--; // counter-clockwise
    } else if (directionZB == 1) {
        encoderPosZB++; // clockwise
    }
}
void handleREncoderB() {
    if (directionRB == 1) { // globalEncoderPosRB can't ever go to zero unless the switch is clicked
        encoderPosRB++; // extending (0 position is fully extended)
        if (encoderPosRB == 0) {
            encoderPosRB = -1;
        }
    } else if (directionRB == -1) {
        encoderPosRB--; // retracting (negative positions)
    }
}
void handleRSwitchB() {
    encoderPosRB = 0;
}
void handleYExtendSwitchB() {
    posYB = 1;
}
void handleYRetractSwitchB() {
    posYB = -1;
}

// BACK ARM
void craneSetupZAxisB() {
    // CRANE Z MOTOR
    pinMode(ZMOTOR_BACK_CW_PIN, OUTPUT);
    pinMode(ZMOTOR_BACK_CCW_PIN, OUTPUT);

    // ENCODER FOR Z MOTOR
    pinMode(ZMOTOR_BACK_ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZMOTOR_BACK_ENCODER_PIN), handleZEncoderB, CHANGE); // on both rising and falling edges
}

void craneSetupRAxisB() {
    // CRANE R MOTOR
    pinMode(RMOTOR_BACK_FORWARD_PIN, OUTPUT);
    pinMode(RMOTOR_BACK_BACKWARD_PIN, OUTPUT);

    ledcSetup(craneRChannelExtendB, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalities
    ledcAttachPin(RMOTOR_BACK_FORWARD_PIN, craneRChannelExtendB); // Attach the PWM channel to the specified pin
    ledcWrite(craneRChannelExtendB, 0);
    
    ledcSetup(craneRChannelRetractB, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalities
    ledcAttachPin(RMOTOR_BACK_BACKWARD_PIN, craneRChannelRetractB); // Attach the PWM channel to the specified pin
    ledcWrite(craneRChannelRetractB, 0);

    // ENCODER FOR R MOTOR
    pinMode(RMOTOR_BACK_ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RMOTOR_BACK_ENCODER_PIN), handleREncoderB, CHANGE); // on both rising and falling edges
    
    // LIMIT SWITCH FOR R MOTOR
    pinMode(RMOTOR_BACK_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RMOTOR_BACK_EXTEND_LIMIT_SWITCH_PIN), handleRSwitchB, FALLING); // on falling edges (switch pressed)
}

void craneSetupYAxisB() {
    // CRANE Y MOTOR
    pinMode(YMOTOR_BACK_UP_PIN, OUTPUT);
    pinMode(YMOTOR_BACK_DOWN_PIN, OUTPUT);

    // LIMIT SWITCHES FOR Y MOTOR
    pinMode(YMOTOR_BACK_EXTEND_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    pinMode(YMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(YMOTOR_BACK_EXTEND_LIMIT_SWITCH_PIN), handleYExtendSwitchB, FALLING); // on falling edges (switch pressed)
    attachInterrupt(digitalPinToInterrupt(YMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN), handleYRetractSwitchB, FALLING); // on falling edges (switch pressed)
}

// MOVEMENT BACK
void craneSetDirectionZB(int dir) {
    encoderPosZB = 0;
    directionZB = dir;
}

bool craneMoveZB(int final_pos) {
    // Rotate either clockwise or counterclockwise (given by sign of final_pos) to final_pos position (in clicks)
    if (directionZB == 1) { // clockwise
        if (encoderPosZB >= final_pos) { // reached position, stop crane
            digitalWrite(ZMOTOR_BACK_CW_PIN, LOW);
            // wsSend("Done Z CW " + String(encoderPosZB) + " final pos " + String(final_pos));
            return true;
        } else { // have not reached position, start/keep rotating
            digitalWrite(ZMOTOR_BACK_CW_PIN, HIGH);
            return false;
        }
        
    } else if (directionZB == -1) { // counter-clockwise
        if (encoderPosZB <= final_pos) { // reached position, stop crane
            digitalWrite(ZMOTOR_BACK_CCW_PIN, LOW);
            // wsSend("Done Z CCW " + String(encoderPosZB)); 
            return true;
        } else { // have not reached position, start/keep rotating
            digitalWrite(ZMOTOR_BACK_CCW_PIN, HIGH);
            return false;
        }
    } else {
        return false;
    }
}

void craneSetDirectionRB(int dir) {
    directionRB = dir;
}

bool craneMoveRB(int finalPos) {
    if (directionRB == 1) { // extending
        if (encoderPosRB == 0) {
            ledcWrite(craneRChannelExtendB, 0);
            // wsSend("Done R forward " + String(encoderPosRB)); 
            return true;
        // } else if (abs(encoderPosRB) < 25) {
        //     ledcWrite(craneRChannelExtendB, 175);
        //     return false;
        } else {
            ledcWrite(craneRChannelExtendB, 200);
            return false;
        }

    } else if (directionRB == -1) { // backward
        if (encoderPosRB <= finalPos) { 
            ledcWrite(craneRChannelRetractB, 0);
            // wsSend("Done R backward " + String(encoderPosRB));
            return true;
        // } else if (abs(encoderPosRB - finalPos) < 10) {
        //     ledcWrite(craneRChannelRetractB, 150);
        //     return false;
        } else {
            ledcWrite(craneRChannelRetractB, 200);
            return false;
        }
    } else {
        return false;
    }
}

void craneSetDirectionYB(int dir) {
    // pass
}

bool craneMoveYB(int finalPos) {
    if (finalPos == -1) { // Retract
        if (posYB == -1) {
            digitalWrite(YMOTOR_BACK_UP_PIN, LOW);
            // wsSend("Done Y up " + String(posYB));
            return true;
        } else {
            digitalWrite(YMOTOR_BACK_UP_PIN, HIGH);
            return false;
        }
    } else { // Extend
        if (posYB == 1) {
            digitalWrite(YMOTOR_BACK_DOWN_PIN, LOW);
            // wsSend("Done Y down " + String(posYB)); 
            return true;
        } else {
            digitalWrite(YMOTOR_BACK_DOWN_PIN, HIGH);
            return false;
        }
    }
}

void craneSetupB() {
    craneSetupZAxisB();
    craneSetupRAxisB();
    craneSetupYAxisB();
}











// FRONT ARM
volatile int encoderPosZF = 0;
volatile int directionZF = 0; // 0 is nothing, 1 is clockwise, -1 is counter-clockwise
volatile int encoderPosRF = 0;
volatile int directionRF = 0; // 0 is nothing, 1 is forward, -1 is backward
volatile int posYF = -1; // -1 is up (retracted), 1 is down (extended), starts retracted

int craneZChannelF = 0;                                                                      
int craneRChannelF = 1;  
int craneYChannelF = 2; 

void handleZEncoderF() {
    // Check the direction of rotation 
    if (directionZF == -1) {
        encoderPosZF--; // counter-clockwise
    } else if (directionZF == 1) {
        encoderPosZF++; // clockwise
    } else {
        // Check line B?
    }
}
void handleREncoderF() {
    // Check the direction of rotation
    if (digitalRead(RMOTOR_FRONT_ENCODER_PIN_B) == HIGH) {
        encoderPosRF++;
    } else {
        encoderPosRF--;
    }
}
void handleYExtendSwitchF() {
    posYF = 1;
}
void handleYRetractSwitchF() {
    posYF = -1;
}
void craneSetupZAxisF() {
    // CRANE Z MOTOR
    pinMode(ZMOTOR_FRONT_CW_PIN, OUTPUT);
    pinMode(ZMOTOR_FRONT_CCW_PIN, OUTPUT);

    ledcSetup(craneZChannelF, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalities
    ledcWrite(craneZChannelF, 0); // Set duty cycle to 0% (127/255)

    // ENCODER FOR Z MOTOR
    pinMode(ZMOTOR_FRONT_ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ZMOTOR_FRONT_ENCODER_PIN), handleZEncoderF, CHANGE); // on both rising and falling edges
}
void craneSetupRAxisF() {
    // CRANE R MOTOR
    pinMode(RMOTOR_FRONT_FORWARD_PIN, OUTPUT);
    pinMode(RMOTOR_FRONT_BACKWARD_PIN, OUTPUT);

    ledcSetup(craneRChannelF, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalities
    ledcWrite(craneRChannelF, 0); // Set duty cycle to 0% (127/255)

    // ENCODER FOR R MOTOR
    pinMode(RMOTOR_FRONT_ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RMOTOR_FRONT_ENCODER_PIN), handleREncoderF, CHANGE); // on both rising and falling edges
}
void craneSetupYAxisF() {
    // CRANE Y MOTOR
    pinMode(YMOTOR_FRONT_UP_PIN, OUTPUT);
    pinMode(YMOTOR_FRONT_DOWN_PIN, OUTPUT);
    
    ledcSetup(craneYChannelF, CranePWMFreq, CranePWMResolution); // Configure the PWM functionalities
    ledcWrite(craneYChannelF, 0); // Set duty cycle to 0% (127/255)

    // LIMIT SWITCHES FOR Y MOTOR
    pinMode(YMOTOR_FRONT_EXTEND_LIMIT_SWITCH_PIN, INPUT);
    pinMode(YMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(YMOTOR_FRONT_EXTEND_LIMIT_SWITCH_PIN), handleYExtendSwitchF, FALLING); // on falling edges (switch pressed)
    attachInterrupt(digitalPinToInterrupt(YMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN), handleYRetractSwitchF, FALLING); // on falling edges (switch pressed)
}
void craneSetDirectionZF(int dir) {
    directionZF = dir;
    if (dir == 1) {
        ledcDetachPin(ZMOTOR_FRONT_CCW_PIN); // Detach the PWM channel from the specified pin
        ledcAttachPin(ZMOTOR_FRONT_CW_PIN, craneZChannelF); // Attach the PWM channel to the specified pin
        ledcWrite(craneZChannelF, 255);
    } else if (dir == -1) {
        ledcDetachPin(ZMOTOR_FRONT_CW_PIN); // Detach the PWM channel from the specified pin
        ledcAttachPin(ZMOTOR_FRONT_CCW_PIN, craneZChannelF); // Attach the PWM channel to the specified pin
        ledcWrite(craneZChannelF, 255);
    } else {
        ledcWrite(craneZChannelF, 0);
        ledcWrite(craneZChannelF, 0);
    }
}
bool craneMoveZF(int final_pos) {
    // Rotate either clockwise or counterclockwise (given by sign of final_pos) to final_pos position (in clicks)
    if (final_pos > 0) { // clockwise
        if (encoderPosZF >= final_pos) { // reached position, stop crane
            ledcWrite(craneZChannelF, 0);
            return true;
        } else { // have not reached position, start/keep rotating
            return false;
        }
    } else { // counter-clockwise
        if (encoderPosZF <= abs(final_pos)) { // reached position, stop crane
            ledcWrite(craneZChannelF, 0);
            return true;
        } else { // have not reached position, start/keep rotating
            return false;
        }
    }
}
void craneSetDirectionRF(int dir) {
    directionRF = dir;
    if (dir == 1) {
        ledcDetachPin(RMOTOR_FRONT_BACKWARD_PIN); // Detach the PWM channel from the specified pin
        ledcAttachPin(RMOTOR_FRONT_FORWARD_PIN, craneRChannelF); // Attach the PWM channel to the specified pin
        ledcWrite(craneRChannelF, 255);
    } else if (dir == -1) {
        ledcDetachPin(RMOTOR_FRONT_FORWARD_PIN); // Detach the PWM channel from the specified pin
        ledcAttachPin(RMOTOR_FRONT_BACKWARD_PIN, craneRChannelF); // Attach the PWM channel to the specified pin
        ledcWrite(craneRChannelF, 255);
    } else {
        ledcWrite(craneRChannelF, 0);
        ledcWrite(craneRChannelF, 0);
    }
}
bool craneMoveRF(int final_pos) {
    if (final_pos > 0) { // forward
        if (encoderPosRF >= final_pos) {
            ledcWrite(craneRChannelF, 0);
            return true;
        } else {
            return false;
        }
    } else { // backward
        if (encoderPosRF <= abs(final_pos)) {
            ledcWrite(craneRChannelF, 0);
            return true;
        } else {
            return false;
        }
    }
}
void craneSetDirectionYF(int dir) {
    if (dir == 1) { // extend
        ledcDetachPin(YMOTOR_FRONT_UP_PIN); // Detach the PWM channel from the specified pin
        ledcAttachPin(YMOTOR_FRONT_DOWN_PIN, craneYChannelF); // Attach the PWM channel to the specified pin
        ledcWrite(craneYChannelF, 255);
    } else if (dir == -1) { // retract
        ledcDetachPin(YMOTOR_FRONT_DOWN_PIN); // Detach the PWM channel from the specified pin
        ledcAttachPin(YMOTOR_FRONT_UP_PIN, craneYChannelF); // Attach the PWM channel to the specified pin
        ledcWrite(craneYChannelF, 255);
    } else {
        ledcWrite(craneYChannelF, 0);
    }
}
bool craneMoveYF(int final_pos) {
    if (final_pos == -1) { // Retract
        if (posYF == -1) {
            ledcWrite(craneYChannelF, 0);
            return true;
        } else {
            return false;
        }
    } else { // Extend
        if (posYF == 1) {
            ledcWrite(craneYChannelF, 0);
            return true;
        } else {
            return false;
        }
    }
}
void craneSetupF() {
    craneSetupZAxisF();
    craneSetupRAxisF();
    craneSetupYAxisF();
}