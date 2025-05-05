#include <msp430.h>
#include "msp430fr2355.h"

#define SERVO_PIN BIT0        // P5.0 for PWM
#define THERMISTOR_PIN BIT0   // P1.0 (A0 for ADC)

// Initialize PWM on P5.0 (TB0.1)
void setupPWM() {
    P5DIR |= SERVO_PIN;       // Set P5.0 as output
    P5SEL0 |= SERVO_PIN;      // Select Timer_B0 for P5.0
    P5SEL1 &= ~SERVO_PIN;    

    TB0CCR0 = 20000;          // 20ms period (50Hz)
    TB0CCR1 = 1500;           // Default mid position (1.5ms pulse)
    TB0CCTL1 = OUTMOD_7;      // Reset/Set mode
    TB0CTL = TASSEL_2 + MC_1; // SMCLK, Up mode
}

// Read thermistor analog value (12-bit ADC)
unsigned int readThermistor() {
    ADCCTL0 |= ADCSHT_2 | ADCON;  // 16 ADCCLK sample time, ADC enabled
    ADCCTL1 |= ADCSHP;            // Use sampling timer
    ADCMCTL0 |= ADCINCH_0;        // Select A0 as input
    ADCCTL0 |= ADCENC | ADCSC;    // Start conversion

    while (ADCCTL1 & ADCBUSY);    // Wait for ADC to finish
    return ADCMEM0;               // Return 12-bit result
}

// Map ADC value (0–4095) to servo angle (0–180)
int mapTempToAngle(unsigned int tempADC) {
    return (tempADC * 180) / 4095;
}

// Convert angle to PWM pulse and set servo
void setServoAngle(int angle) {
    unsigned int duty = 1000 + ((angle * 1000) / 180); // 1ms to 2ms
    TB0CCR1 = duty;
}

// Adjust heat based on temperature reading
void adjustHeatByTemp() {
    unsigned int tempADC = readThermistor();
    int angle = mapTempToAngle(tempADC);
    setServoAngle(angle);
}

// Main program loop
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    // Configure ADC input
    P1SEL0 |= THERMISTOR_PIN;    // Enable A0 for ADC functionality
    P1SEL1 &= ~THERMISTOR_PIN;   

    setupPWM();                  // Setup servo PWM

    while (1) {
        adjustHeatByTemp();      // Continuously adjust heat
        __delay_cycles(100000);  // Delay for stability (~100ms @ 1MHz)
    }
}