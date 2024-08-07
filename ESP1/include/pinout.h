#ifndef PINOUT_H
#define PINOUT_H

// PINS

// Start
extern int START_SWITCH_PIN;

// Oled
extern int OLED_SDA_PIN;
extern int OLED_SCL_PIN;

// BLUEPILL UART
extern int UART_BLUEPILL_TX_PIN; 
extern int UART_BLUEPILL_RX_PIN; 

// ESP2 UART
extern int UART_ESP2_RX_PIN;
extern int UART_ESP2_TX_PIN;

// Vacuum
extern int VACUUM_FRONT_MOTOR_PIN;
extern int VACUUM_BACK_MOTOR_PIN;

// Z-axis rotation for both arms
extern int ZMOTOR_FRONT_CW_PIN;
extern int ZMOTOR_FRONT_CCW_PIN;
extern int ZMOTOR_FRONT_ENCODER_PIN;
extern int ZMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN;

extern int ZMOTOR_BACK_CW_PIN;
extern int ZMOTOR_BACK_CCW_PIN;
extern int ZMOTOR_BACK_ENCODER_PIN;
extern int ZMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN;

// R-axis translation for both arms
extern int RMOTOR_FRONT_FORWARD_PIN;
extern int RMOTOR_FRONT_BACKWARD_PIN;
extern int RMOTOR_FRONT_ENCODER_PIN;
extern int RMOTOR_FRONT_ENCODER_PIN_B;
extern int RMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN;

extern int RMOTOR_BACK_FORWARD_PIN;
extern int RMOTOR_BACK_BACKWARD_PIN;
extern int RMOTOR_BACK_ENCODER_PIN;
extern int RMOTOR_BACK_ENCODER_PIN_B;
extern int RMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN;

// "Y-axis" translation for both arms (called 'YMOTOR' just to differentatiate from the z-axis rotation)
extern int YMOTOR_FRONT_UP_PIN;
extern int YMOTOR_FRONT_DOWN_PIN;
extern int YMOTOR_FRONT_EXTEND_LIMIT_SWITCH_PIN;
extern int YMOTOR_FRONT_RETRACT_LIMIT_SWITCH_PIN;

extern int YMOTOR_BACK_UP_PIN;
extern int YMOTOR_BACK_DOWN_PIN;
extern int YMOTOR_BACK_EXTEND_LIMIT_SWITCH_PIN;
extern int YMOTOR_BACK_RETRACT_LIMIT_SWITCH_PIN;

// Cups
extern int CUP_A_MOTOR_FORWARD_PIN; 
extern int CUP_A_MOTOR_BACKWARD_PIN; 
extern int CUP_A_SERVO_LEFT_PIN; 
extern int CUP_A_SERVO_RIGHT_PIN;
extern int CUP_A_EXTEND_LIMIT_SWITCH_PIN; 
extern int CUP_A_RETRACT_LIMIT_SWITCH_PIN; 

#endif // PINOUT_H
