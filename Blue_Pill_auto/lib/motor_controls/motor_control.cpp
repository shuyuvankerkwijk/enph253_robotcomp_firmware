#include <Arduino.h>
#include <motor_control.h>
#include <globals.h>
// #include "stm32f1xx.h"
// #include "stm32f1xx_hal.h"

void setupPWM() {
    for (int i = 0; i < 4; i++) {
        pinMode(motor_pwm_pins_ints[i], OUTPUT);
        pinMode(motor_d_select_pins[i], OUTPUT);
    }

    // Initialize digital select pins as low
    digitalWrite(motor_d_select_pins[0], HIGH);
    digitalWrite(motor_d_select_pins[1], LOW);
    digitalWrite(motor_d_select_pins[2], LOW);
    digitalWrite(motor_d_select_pins[3], LOW);

    // Initialize PWM channels with a frequency of 1kHz and duty cycle of 0
    pwm_start(motor_pwm_pins[0], 100, 0, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(motor_pwm_pins[1], 100, 0, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(motor_pwm_pins[2], 100, 0, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(motor_pwm_pins[3], 100, 0, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
}

void updateMotorSpeed() {
    for (int i = 0; i < 4; i++) {

        uint32_t speed = abs(motorSpeeds[i]);
        uint32_t duty_cycle = (speed * 4095) / 1000;

        switch(i) {
            case 0:  // Motor 0
                pwm_start(motor_pwm_pins[0], 100, duty_cycle, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
                digitalWrite(motor_d_select_pins[0], motorSpeeds[i] > 0 ? HIGH : LOW);
                break;
            case 1:  // Motor 1
                pwm_start(motor_pwm_pins[1], 100, duty_cycle, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
                digitalWrite(motor_d_select_pins[1], motorSpeeds[i] > 0 ? LOW : HIGH);
                break;
            case 2:  // Motor 2
                pwm_start(motor_pwm_pins[2], 100, duty_cycle, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
                digitalWrite(motor_d_select_pins[2], motorSpeeds[i] > 0 ? LOW : HIGH);
                break;
            case 3:  // Motor 3
                pwm_start(motor_pwm_pins[3], 100, duty_cycle, TimerCompareFormat_t::RESOLUTION_12B_COMPARE_FORMAT);
                digitalWrite(motor_d_select_pins[3], motorSpeeds[i] > 0 ? LOW : HIGH);
                break;
        }
    }
}

// void setupPWM() {
//     // Enable clocks for GPIOB and TIM4
//     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;  // Enable GPIOB clock
//     RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;  // Enable TIM4 clock

//     // Configure GPIOB for Alternate Function Output Push-Pull for PWM pins
//     // PB8 (TIM4_CH3), PB9 (TIM4_CH4), PB6 (TIM4_CH1), PB7 (TIM4_CH2)
//     GPIOB->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9);
//     GPIOB->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0) | 
//                   (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0);

//     GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
//     GPIOB->CRL |= (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE6_0) | 
//                   (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0);

//     // Configure GPIOB for General Purpose Output for D-Select pins
//     // PB14, PB12, PB13
//     GPIOB->CRH &= ~(GPIO_CRH_CNF14 | GPIO_CRH_CNF12 | GPIO_CRH_CNF13| GPIO_CRH_CNF15);
//     GPIOB->CRH |= (GPIO_CRH_MODE14_1 | GPIO_CRH_MODE14_0) | 
//                   (GPIO_CRH_MODE12_1 | GPIO_CRH_MODE12_0) | 
//                   (GPIO_CRH_MODE15_1 | GPIO_CRH_MODE15_0) | 
//                   (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0);

//     // Setup TIM4 for PWM on channels 1, 2, 3, and 4
//     TIM4->PSC = 7200 - 1;  // Prescaler to achieve 10kHz
//     TIM4->ARR = 1000 - 1;  // Auto-reload for 100Hz PWM frequency

//     // Configure PWM mode and enable channels
//     TIM4->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE) |  // PWM mode 1 for CH1
//                   (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE);   // PWM mode 1 for CH2
//     TIM4->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE) |  // PWM mode 1 for CH3
//                   (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE);   // PWM mode 1 for CH4

//     TIM4->CCER = TIM_CCER_CC1E |  // Enable CH1, active high
//                  TIM_CCER_CC2E |  // Enable CH2, active high
//                  TIM_CCER_CC3E |  // Enable CH3, active high
//                  TIM_CCER_CC4E;   // Enable CH4, active high

//     TIM4->CR1 |= TIM_CR1_CEN;  // Enable TIM4
// }

// void updateMotorSpeed() {
//     for (int i = 0; i < 4; i++) {
//         uint32_t speed = (motorSpeeds[i] > 0) ? (uint32_t)(motorSpeeds[i]) : (uint32_t)(-motorSpeeds[i]);

//         switch(i) {
//             case 0:  // Motor 0
//                 TIM4->CCR3 = speed;
//                 digitalWrite(motor_d_select_pins[0], motorSpeeds[i] > 0 ? LOW : HIGH);
//                 break;
//             case 1:  // Motor 1
//                 TIM4->CCR4 = speed;
//                 digitalWrite(motor_d_select_pins[1], motorSpeeds[i] > 0 ? LOW : HIGH);
//                 break;
//             case 2:  // Motor 2
//                 TIM4->CCR2 = speed;
//                 digitalWrite(motor_d_select_pins[2], motorSpeeds[i] > 0 ? LOW : HIGH);
//                 break;
//             case 3:  // Motor 3
//                 TIM4->CCR1 = speed;
//                 digitalWrite(motor_d_select_pins[3], motorSpeeds[i] > 0 ? LOW : HIGH);
//                 break;
//         }
//     }
// }

// #include "stm32f1xx.h"
// #include "stm32f1xx_hal.h"
// #include "motor_control.h"

// /**
//  *    PWM   D-Select    
//  * M0 B8    B14
//  * M1 B9    B15
//  * M2 B6    B12
//  * M3 B7    B13
//  */

// void setupPWM() {
//     // Enable clocks for GPIOB and TIM4
//     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;  // Enable GPIOB clock
//     RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;  // Enable TIM4 clock

//     // Configure GPIOB for Alternate Function Output Push-Pull for PWM pins
//     // PB8 (TIM4_CH3), PB9 (TIM4_CH4), PB6 (TIM4_CH1), PB7 (TIM4_CH2)
//     GPIOB->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9);
//     GPIOB->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0) | 
//                   (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0);

//     GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
//     GPIOB->CRL |= (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE6_0) | 
//                   (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0);

//     // Configure GPIOB for General Purpose Output for D-Select pins
//     // PB14, PB12, PB13
//     GPIOB->CRH &= ~(GPIO_CRH_CNF14 | GPIO_CRH_CNF12 | GPIO_CRH_CNF13| GPIO_CRH_CNF15);
//     GPIOB->CRH |= (GPIO_CRH_MODE14_1 | GPIO_CRH_MODE14_0) | 
//                   (GPIO_CRH_MODE12_1 | GPIO_CRH_MODE12_0) | 
//                   (GPIO_CRH_MODE15_1 | GPIO_CRH_MODE15_0) | 
//                   (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0);

//     // Setup TIM4 for PWM on channels 1, 2, 3, and 4
//     TIM4->PSC = 720 - 1;  // Prescaler to achieve 1000 Hz
//     TIM4->ARR = 100 - 1;  // Auto-reload for 1kHz PWM frequency

//     // Configure PWM mode and enable channels
//     TIM4->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE) |  // PWM mode 1 for CH1
//                   (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE);   // PWM mode 1 for CH2
//     TIM4->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE) |  // PWM mode 1 for CH3
//                   (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE);   // PWM mode 1 for CH4

//     TIM4->CCER = TIM_CCER_CC1E |  // Enable CH1, active high
//                  TIM_CCER_CC2E |  // Enable CH2, active high
//                  TIM_CCER_CC3E |  // Enable CH3, active high
//                  TIM_CCER_CC4E;   // Enable CH4, active high

//     TIM4->CR1 |= TIM_CR1_CEN;  // Enable TIM4
// }

// void updateMotorSpeed() {
//     for (int i = 0; i < 4; i++) {
//         uint32_t speed = (motorSpeeds[i] > 0) ? (uint32_t)(motorSpeeds[i]) : (uint32_t)(-motorSpeeds[i]);

//         switch(i) {
//             case 0:  // Motor 0
//                 TIM4->CCR3 = speed;
//                 if (motorSpeeds[i] > 0) {
//                     GPIOB->BSRR = GPIO_BSRR_BR14;  // Set PB14 low
//                 } else {
//                     GPIOB->BSRR = GPIO_BSRR_BS14;  // Set PB14 high
//                 }
//                 break;
//             case 1:  // Motor 1
//                 TIM4->CCR4 = speed;
//                 if (motorSpeeds[i] > 0) {
//                     GPIOB->BSRR = GPIO_BSRR_BR15;  // Set PB15 low
//                 } else {
//                     GPIOB->BSRR = GPIO_BSRR_BS15;  // Set PB15 high
//                 }
//                 break;
//             case 2:  // Motor 2
//                 TIM4->CCR2 = speed;
//                 if (motorSpeeds[i] > 0) {
//                     GPIOB->BSRR = GPIO_BSRR_BR13;  // Set PB13 low
//                 } else {
//                     GPIOB->BSRR = GPIO_BSRR_BS13;  // Set PB13 high
//                 }
//                 break;
//             case 3:  // Motor 3
//                 TIM4->CCR1 = speed;
//                 if (motorSpeeds[i] > 0) {
//                     GPIOB->BSRR = GPIO_BSRR_BS12;  // Set PB12 high
//                 } else {
//                     GPIOB->BSRR = GPIO_BSRR_BR12;  // Set PB12 low
//                 }
//                 break;
//         }
//     }
// }