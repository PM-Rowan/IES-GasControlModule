#include <msp430.h>
#include "msp430fr2355.h"

#define SERVO_PIN     BIT4      // P1.4 (Timer_A output)
#define BUTTON_PIN    BIT3      // P2.3
#define DEBOUNCE_TIME 20000

volatile int valveOpen = 0;

// Set servo angle in degrees (0–180)
void setServoAngle(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    // Map angle to pulse width (1ms–2ms = 5%–10% of 20ms period)
    int pulse = 1000 + (angle * 1000) / 180; // in µs

    TACCR1 = (pulse * 1000) / 20000; // Scale to timer ticks for 1MHz
}

// Simple delay for debouncing
void debounce() {
    __delay_cycles(DEBOUNCE_TIME);
}

// Button ISR (manual override)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    debounce();

    valveOpen ^= 1; // Toggle valve state
    if (valveOpen) {
        setServoAngle(90); // Open valve
    } else {
        setServoAngle(0);  // Close valve
    }

    P2IFG &= ~BUTTON_PIN; // Clear interrupt flag
}

void setupPWM() {
    P1DIR |= SERVO_PIN;
    P1SEL |= SERVO_PIN;  // Enable PWM on P1.4

    TA0CCR0 = 20000 - 1;     // 20ms period @ 1MHz (50Hz)
    TA0CCTL1 = OUTMOD_7;     // Reset/set mode
    TA0CCR1 = 1500;          // Initial pulse width (~1.5ms = center)
    TA0CTL = TASSEL_2 + MC_1;// SMCLK, up mode
}

void setupButton() {
    P2DIR &= ~BUTTON_PIN;    // Input
    P2REN |= BUTTON_PIN;     // Enable pull-up/down
    P2OUT |= BUTTON_PIN;     // Pull-up
    P2IE  |= BUTTON_PIN;     // Enable interrupt
    P2IES |= BUTTON_PIN;     // High-to-low transition
    P2IFG &= ~BUTTON_PIN;    // Clear flag
}

void setup() {
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog
    BCSCTL1 = CALBC1_1MHZ;     // Clock config
    DCOCTL = CALDCO_1MHZ;

    setupPWM();
    setupButton();

    __enable_interrupt();      // Enable global interrupts
}

void main(void) {
    setup();

    while (1) {
        // Main loop could monitor other logic, like auto shutoff, sensors, etc.
        __no_operation(); // Idle
    }
}
