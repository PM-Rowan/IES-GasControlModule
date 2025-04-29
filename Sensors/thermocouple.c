#include <msp430.h>
#include "msp430fr2355.h"

#define THERMOCOUPLE_PIN BIT0  // P1.0 = A0
#define ADC_CHANNEL       0    // Channel A0

// Manually set desired temperature in Celsius
int desiredTemp = 200; // Example threshold

// Read temperature from thermocouple (assuming 10 mV/°C output after amplification)
int readThermocoupleTemp() {
    ADC10CTL0 = ADC10SHT_3 + ADC10ON;
    ADC10CTL1 = ADC_CHANNEL;
    ADC10AE0 |= THERMOCOUPLE_PIN;

    ADC10CTL0 |= ENC + ADC10SC;            // Start ADC
    while (ADC10CTL1 & ADC10BUSY);         // Wait for conversion

    unsigned int adcValue = ADC10MEM;

    // Convert ADC value to voltage
    float voltage = adcValue * (3.3 / 1024.0);  // Assuming 3.3V Vref

    // Amplified thermocouple: 10 mV/°C → Temp = voltage (in V) / 0.01
    int temperature = (int)(voltage / 0.01);

    return temperature;
}

void setup() {
    BCSCTL1 = CALBC1_1MHZ;     // Set clock to 1 MHz
    DCOCTL = CALDCO_1MHZ;

    // Optional: configure output pin to indicate over-temp
    P1DIR |= BIT6;  // Set P1.6 as output
    P1OUT &= ~BIT6; // Initially off
}

void main(void) {
    setup();

    while (1) {
        int temp = readThermocoupleTemp();

        if (temp >= desiredTemp) {
            P1OUT |= BIT6;  // Turn on alert (e.g., LED or signal)
        } else {
            P1OUT &= ~BIT6;
        }

        __delay_cycles(500000); // Wait between checks
    }
}

