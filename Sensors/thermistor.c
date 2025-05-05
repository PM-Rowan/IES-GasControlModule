#include <msp430.h>
#include "msp430fr2355.h"

#define SERVO_PIN BIT0       // P5.0
#define THERMISTOR_PIN BIT0  // P1.0 (A0)

// Initialize PWM on P5.0 (TA0.1)
void setupPWM() {
    P5DIR |= SERVO_PIN;      // Set P5.0 as output
    P5SEL |= SERVO_PIN;      // Select TA0.1 for P5.0

    TA0CCR0 = 20000;         // 20ms period (50Hz)
    TA0CCR1 = 1500;          // Default mid position (1.5ms pulse)
    TA0CCTL1 = OUTMOD_7;     // Reset/Set mode
    TA0CTL = TASSEL_2 + MC_1; // SMCLK, Up mode
}

// Read thermistor analog value (10-bit ADC from A0)
unsigned int readThermistor() {
    ADC10CTL1 = INCH_0; // Channel A0
    ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ENC + ADC10SC;
    while (ADC10CTL1 & ADC10BUSY); // Wait for ADC to finish
    return ADC10MEM;
}

// Map 10-bit ADC value (0–1023) to servo angle (0–180)
int mapTempToAngle(unsigned int tempADC) {
    return (tempADC * 180) / 1023;
}

// Convert angle to PWM pulse and set servo
void setServoAngle(int angle) {
    unsigned int duty = 1000 + ((angle * 1000) / 180); // 1ms to 2ms
    TA0CCR1 = duty;
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
    ADC10AE0 |= THERMISTOR_PIN;  // Enable analog on P1.0

    setupPWM();                  // Setup servo PWM

    while (1) {
        adjustHeatByTemp();     // Continuously adjust heat
        __delay_cycles(100000); // Delay for stability (~100ms @ 1MHz)
    }
}

