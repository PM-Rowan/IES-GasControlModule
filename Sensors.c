/*
This will apply for:
- Thermistor [Main Valve Chamber]
- Thermocouple [Pilot Light]
- Potentiometer [Boiler Set Point]
*/

#include "intrinsics.h"
#include "msp430fr2355.h"
#include <thread>

#include "GLOBAL.h"

void adc_Init() 
{
    // P1.(1, 3, 4, 5) -> A(1, 3, 4, 5)
    P1DIR |= BIT1 | BIT3 | BIT4 | BIT5;

    P1SEL0 |= BIT1 | BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT1 | BIT3 | BIT4 | BIT5;

    // wait setting
    ADCCTL0 |= ADCSHT_2;
    ADCCTL0 |= ADCON;
    
    ADCCTL1 |= ADCSSEL_2;
    ADCCTL1 |= ADCSHP; 

    ADCCTL2 &= ~ADCRES; // 12 bit
    ADCCTL2 |= ADCRES_2; 
    ADCCTL2 &= ~ADCDF; // unsigned format

    // Reset ADC Mux to A0 (0000)
    ADCMCTL0 &= ~ADCINCH0 | ~ADCINCH1 | ~ADCINCH2 | ~ADCINCH3; 
}

// Reads input pin and outputs 12bit value (15-12 are 0)
unsigned int readADC(char sensorSelect) 
{
    // A3 -> Thermocouple:  sensorSelect = 3
    // A4 -> Thermistor:    sensorSelect = 4
    // A5 -> Potentiometer: sensorSelect = 5
    // Else -> Nothing:     sensorSelect = x

    // Only bits 1 & 0
    ADCMCTL0 &= sensorSelect;

    while( (ADCIV0 & ADCIFG0) == 0);

    return 
}

void quickRead() // Read all possible ADC Inputs, A0 -> A15
{
    while(int x = 0; i < 16; i = i + 1) 
    {
        ADCMCTL0 &= sensorSelect + 3;

        while( (ADCIV0 & ADCIFG0) == 0);

        ADC_AX[i] = ADC;
    }
}