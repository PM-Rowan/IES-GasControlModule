Potentiometer: 
#include <msp430.h>

#define POT_PIN    BIT0     // P1.0 (A0)
#define LED_PIN    BIT6     // P1.6 (for output indicator like an LED)
#define ADC_CHANNEL 0       // A0

// Set desired temperature manually (0–100 for example)
int desiredTemp = 50;

// Convert potentiometer ADC value (0–1023) to 0–100 scale
int readPotAsTemperature() {
    ADC10CTL0 = ADC10SHT_3 + ADC10ON;      // Sample and hold time, ADC on
    ADC10CTL1 = ADC_CHANNEL;               // Input from A0
    ADC10AE0 |= POT_PIN;                   // Enable analog input on P1.0

    ADC10CTL0 |= ENC + ADC10SC;            // Start conversion
    while (ADC10CTL1 & ADC10BUSY);         // Wait for it to finish

    unsigned int adcVal = ADC10MEM;

    // Scale 0–1023 to 0–100 as a simulated temperature
    int temperature = (adcVal * 100) / 1023;

    return temperature;
}

void setup() {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    BCSCTL1 = CALBC1_1MHZ;      // Clock settings
    DCOCTL = CALDCO_1MHZ;

    P1DIR |= LED_PIN;           // Set P1.6 as output (e.g. LED)
    P1OUT &= ~LED_PIN;          // Start with LED off
}

void main(void) {
    setup();

    while (1) {
        int currentTemp = readPotAsTemperature();

        if (currentTemp >= desiredTemp) {
            P1OUT |= LED_PIN;   // Turn on LED if temp is high
        } else {
            P1OUT &= ~LED_PIN;  // Turn off LED if below threshold
        }

        __delay_cycles(500000); // Delay for readability
    }
}
