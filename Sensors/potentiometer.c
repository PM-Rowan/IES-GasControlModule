#include "msp430fr2355.h"
#include <msp430.h>

#define POT_PIN    BIT5     // P1.5 (A5)
#define LED_PIN    BIT6     // P1.6 (for output indicator like an LED)
#define ADC_CHANNEL 0       // ADC channel for A0

void setup() {
    WDTCTL = WDTPW | WDTHOLD;   // Stop the watchdog timer

    // Configure LED pin as output
    P1DIR |= LED_PIN;
    P1OUT &= ~LED_PIN;          // Start with LED off

    // Configure P1.5 (A5) for ADC input
    P1SEL0 |= POT_PIN;         
    P1SEL1 |= POT_PIN;

    // Configure ADC settings
    ADCCTL0 = ADCSHT_2 | ADCON;    // Sample & hold time, ADC on
    ADCCTL1 = ADCSHP;              // Sampling signal from sample timer
    ADCCTL2 = ADCRES;              // Use 12-bit resolution
    ADCMCTL0 = ADC_CHANNEL;        // Select A0 as input channel
}

unsigned int readADC() {
    ADCCTL0 |= ADCENC | ADCSC;     // Enable ADC and start conversion
    while (ADCCTL1 & ADCBUSY);     // Wait for conversion to finish
    
    return ADCMEM0;                // Read ADC result
}

void loop() {
    unsigned int adcVal = readADC();  
    int temperature = (adcVal * 100) / 4095; // Scale ADC value to 0–100 range
    
    if (temperature > 50) {
        P1OUT |= LED_PIN;  // Turn on LED if temperature is above threshold
    } else {
        P1OUT &= ~LED_PIN; // Turn off LED otherwise
    }
}