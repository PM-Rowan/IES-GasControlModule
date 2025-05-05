#include "msp430fr2355.h"
#include <msp430.h>

#define THERMOCOUPLE_PIN BIT3
#define DESIRED_TEMP 75  // Desired temperature threshold in °C

void thermocouple_init() {
    // Configure output pin for over-temp indication
    P1DIR |= BIT3;  // Set P1.6 as output
    P1OUT &= ~BIT3; // Initially off
}

int readThermocoupleTemp() {
    unsigned int adcValue;
    float voltage;
    float temperature;

    ADCCTL0 |= ADCSC;                 // Start conversion
    while (ADCCTL1 & ADCBUSY);        // Wait for conversion to complete
    adcValue = ADCMEM0;               // Read ADC value

    voltage = (float)adcValue * 3.3 / 1023;  // Convert ADC value to voltage (3.3V ref)
    temperature = (voltage - 1.25) / 0.005;  // Example for Type K thermocouple

    return (int)temperature;
}

bool isFlameDetected(int temperature, int flameThreshold) {
    return temperature >= flameThreshold;
}

void runFlameDetection() {
    initThermocoupleADC();

        int temp = readThermocoupleTemp();

        if (isFlameDetected(temp, DESIRED_TEMP)) {
            P1OUT |= BIT3;  // Turn on alert (e.g., LED or signal)
        } else {
            P1OUT &= ~BIT3; // Turn off alert
        }

        __delay_cycles(500000); // Wait between checks
    
}