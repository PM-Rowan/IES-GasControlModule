#include <msp430.h>
#include "msp430fr2355.h"

#include "GLOBAL.h"
volatile unsigned char valveOpenDegrees = 0;
volatile unsigned char valveOpen = 0;

unsigned int valveCalc = 0;

#define SERVO_PIN     BIT0      // P5.0
#define BUTTON_PIN    BIT3      // P2.3
#define DEBOUNCE_TIME 20000

// Set servo angle in degrees (0–90)
void setServoAngle(char newAngle) {

    if (newAngle > 90) valveOpenDegrees = 90;
    else valveOpenDegrees = newAngle;

    valveCalc = (newAngle * 3) + 15000;
    TB2CCR1 = (newAngle * 3) + 15000; // Scale to timer ticks for 1MHz [15k, 15270]
}

void updateAngle() {
    TB2CCR1 = (valveOpenDegrees * 3) + 15000; // Scale to timer ticks for 1MHz [15k, 15270]
}

// Button ISR (manual override)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {

    valveOpen ^= 0xFF; // Toggle valve state
    if (valveOpen) {
        setServoAngle(90); // Open valve
    } else {
        setServoAngle(0);  // Close valve
    }

    P2IFG &= ~BUTTON_PIN; // Clear interrupt flag
}

void setupPWM() {
    P5DIR |= SERVO_PIN;  // Set P5.0 as output
    P5SEL0 |= SERVO_PIN;  // Enable PWM on P5.0


    // Config TB2.1
    TB2CCR0 = DEBOUNCE_TIME - 1;     // 20ms period @ 1MHz (50Hz)
    TB2CCTL1 = OUTMOD_3;     // Reset/set mode
    TB2CCR1 = 1500;          // Initial pulse width (~1.5ms = center)
    TB2CTL = TBSSEL_2 + MC_1;// SMCLK, up mode
}

void setupButton() {
    P2DIR &= ~BUTTON_PIN;    // Input
    P2REN |= BUTTON_PIN;     // Enable pull-up/down
    P2OUT |= BUTTON_PIN;     // Pull-up
    P2IE  |= BUTTON_PIN;     // Enable interrupt
    P2IES |= BUTTON_PIN;     // High-to-low transition
    P2IFG &= ~BUTTON_PIN;    // Clear flag
}

void mainGasValve_init() {
    setupPWM();
    setupButton();
}