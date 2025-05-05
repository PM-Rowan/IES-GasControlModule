#include <msp430.h>
#include "msp430fr2355.h"

#define SERVO_PIN BIT0        // P5.0 for PWM
#define THERMISTOR_PIN BIT0   // P1.0 (A0 for ADC)

// Initialize PWM on P5.0 (TB0.1)
void thermistor_init() {
    P5DIR |= SERVO_PIN;       // Set P5.0 as output
    P5SEL0 |= SERVO_PIN;      // Select Timer_B0 for P5.0
    P5SEL1 &= ~SERVO_PIN;    

    TB0CCR0 = 20000;          // 20ms period (50Hz)
    TB0CCR1 = 1500;           // Default mid position (1.5ms pulse)
    TB0CCTL1 = OUTMOD_7;      // Reset/Set mode
    TB0CTL = TASSEL_2 + MC_1; // SMCLK, Up mode
}