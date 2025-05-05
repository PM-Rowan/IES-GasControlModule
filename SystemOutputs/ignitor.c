#include "msp430fr2355.h"
#include <msp430.h>

void ignitor_init() 
{
    P2DIR |= BIT5; // Set P2.5 as an output
    P2OUT &= ~BIT5; // Set P2.5 to LOW   
}

void ignite() 
{
    P2OUT |= BIT5; // Set P2.5 to HIGH
}

void deignite()
{
    P2OUT &= ~BIT5; // Set P2.5 to LOW
}