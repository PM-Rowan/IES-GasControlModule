#include <msp430.h>
#include "msp430fr2355.h"

#include "mainGasValve.h"

#define SOLENOID_PIN   BIT0      // P2.0: controls solenoid (adjust as needed)
#define BUTTON_PIN     BIT1      // P4.1: manual override button
#define DEBOUNCE_TIME  20000

// Interrupt service routine for manual override
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void) {

    P2OUT ^= 0x0001; // Toggle state

    P4IFG &= ~BUTTON_PIN; // Clear interrupt flag
}

void pilotGasValve_open() {
    P2OUT &= ~SOLENOID_PIN; // Set P2.1 to on
}

void pilotGasValve_close() {
    P2OUT |= SOLENOID_PIN; // Set P2.1 to off
}

void pilotGasValve_init() {

    // Solenoid Config
    P2DIR |= SOLENOID_PIN;        // Configure solenoid pin as output
    P2OUT &= ~SOLENOID_PIN;       // Start with solenoid OFF

    // Configure button on P4.1
    P4DIR &= ~BUTTON_PIN;         // Set as input
    P4REN |= BUTTON_PIN;          // Enable pull-up/down
    P4OUT |= BUTTON_PIN;          // Pull-up
    P4IE  |= BUTTON_PIN;          // Interrupt enable
    P4IES |= BUTTON_PIN;          // Falling edge
    P4IFG &= ~BUTTON_PIN;         // Clear flag
}