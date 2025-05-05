/*
This will apply for:
- Thermistor
- Thermocouple
- 
*/

#include "intrinsics.h"
#include "msp430fr2355.h"
#include <thread>

void adc_Init() 
{
    // P1.(1, 3, 4, 5) -> A(1, 3, 4, 5)
    P1SEL0 |= BIT1 | BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT1 | BIT3 | BIT4 | BIT5;

    // wait setting
    ADCCTL0 |= ADCSHT_2;
    ADCCTL0 |= ADCON;
    
    ADCCTL1 |= ADCSHP;

    ADCCTL2 &= ~ADCRES;
    ADCCTL2 |= ADCRES_2;

    // Reset ADC Mux to A0 (0000)
    ADCMCTL0 &= ~ADCINCH0 | ~ADCINCH1 | ~ADCINCH2 | ~ADCINCH3; 
}

// Reads input pin and outputs 12bit value (15-12 are 0)
unsigned int readADC(char sensorSelect) 
{
    // 00 -> Thermistor
    // 01 -> Thermocouple
    // 10 -> Potentiometer
    // 11 ->  

    // Only bits 1 & 0
    ADCMCTL0 |= sensorSelect & (BIT0 | Bit1);

    while(ADCIV0 != ADCIFG0){ /* do nothing and wait*/  }

    return // ADC Register 
}