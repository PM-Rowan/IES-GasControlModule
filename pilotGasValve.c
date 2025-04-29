#include <msp430.h>

#define SOLENOID_PIN   BIT0      // P4.0: controls solenoid (adjust as needed)
#define BUTTON_PIN     BIT1      // P4.1: manual override button
#define DEBOUNCE_TIME  20000

volatile int valveState = 0;

// Debounce helper
void debounce() {
    __delay_cycles(DEBOUNCE_TIME);
}

// Interrupt service routine for manual override
#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void) {
    debounce();

    valveState ^= 1; // Toggle state

    if (valveState) {
        P4OUT |= SOLENOID_PIN;  // Turn ON solenoid (open valve)
    } else {
        P4OUT &= ~SOLENOID_PIN; // Turn OFF solenoid (close valve)
    }

    P4IFG &= ~BUTTON_PIN; // Clear interrupt flag
}

void setup() {
    WDTCTL = WDTPW | WDTHOLD;     // Stop watchdog

    // Configure solenoid pin as output
    P4DIR |= SOLENOID_PIN;
    P4OUT &= ~SOLENOID_PIN;       // Start with solenoid OFF

    // Configure button on P4.1
    P4DIR &= ~BUTTON_PIN;         // Set as input
    P4REN |= BUTTON_PIN;          // Enable pull-up/down
    P4OUT |= BUTTON_PIN;          // Pull-up
    P4IE  |= BUTTON_PIN;          // Interrupt enable
    P4IES |= BUTTON_PIN;          // Falling edge
    P4IFG &= ~BUTTON_PIN;         // Clear flag

    __enable_interrupt();         // Enable global interrupts
}

void main(void) {
    setup();

    while (1) {
        __no_operation();         // Low-power wait loop
    }
}

Flame Retry System:
#define MAIN_VALVE_CLOSE_ANGLE   0
#define MAIN_VALVE_OPEN_ANGLE    90

#define IGNITOR_PIN   BIT2   // Assume P1.2
#define SOLENOID_PIN  BIT0   // Assume P4.0

// Helper: Close all valves and shut off ignitor
void shutdownAll() {
    setServoAngle(MAIN_VALVE_CLOSE_ANGLE);   // Close main valve
    P4OUT &= ~SOLENOID_PIN;                 // Close pilot valve
    P1OUT &= ~IGNITOR_PIN;                  // Turn off ignitor
}

// Helper: Turn on ignitor and open valves
void restartAll() {
    P1OUT |= IGNITOR_PIN;                   // Turn on ignitor
    setServoAngle(MAIN_VALVE_OPEN_ANGLE);   // Open main valve
    P4OUT |= SOLENOID_PIN;                  // Open pilot valve
}

// Flame retry sequence
void flameRetrySequence() {
    shutdownAll();                  // Step 1–3
    __delay_cycles(5000000);        // Step 4: Wait ~5s at 1MHz (adjust as needed)
    restartAll();                   // Step 5: Retry
}

