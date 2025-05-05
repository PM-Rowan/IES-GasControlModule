#include <msp430.h>
#include "msp430fr2355.h"

#include "Valves/mainGasValve.h"

// Flame Retry System:
#define MAIN_VALVE_CLOSE_ANGLE   0
#define MAIN_VALVE_OPEN_ANGLE    90

#define IGNITOR_PIN   BIT5   // Assume P2.5
#define SOLENOID_PIN  BIT0   // Assume P2.0


void shutdownAll();
void restartAll();

// Flame retry sequence
void flameRetrySequence() {
    shutdownAll();                  // Closes Everything
    __delay_cycles(5000000);        // REPLACE WITH PILOT_LIGHT_TIMER
    restartAll();                   // Opens Everything
}

// Helper: Close all valves and shut off ignitor
void shutdownAll() {
    setServoAngle(MAIN_VALVE_CLOSE_ANGLE);   // Close main valve
    P2OUT &= ~SOLENOID_PIN;                 // Close pilot valve
    P2OUT &= ~IGNITOR_PIN;                  // Turn off ignitor
}

// Helper: Turn on ignitor and open valves
void restartAll() {
    P2OUT |= IGNITOR_PIN;                   // Turn on ignitor
    setServoAngle(MAIN_VALVE_OPEN_ANGLE);   // Open main valve
    P2OUT |= SOLENOID_PIN;                  // Open pilot valve
}