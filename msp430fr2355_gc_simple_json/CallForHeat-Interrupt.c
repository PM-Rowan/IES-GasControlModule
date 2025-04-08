#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>

void CallForHeat();

int CallForHeat_init(void)
{
    P4DIR &= ~BIT1; // P4.1 button is input
    P4REN |= BIT1; // Enable Resistor
    P4OUT |= BIT1; // Pull-up
    P4IES |= BIT1; // H to L

    PM5CTL0 &= ~LOCKLPM5; // turns on digital IO

    P4IE |= BIT1; // enables IRQ 
    __enable_interrupt(); 
    P4IFG &= ~BIT1; 
}

// Interrupt when Logical "HIGH" (1) is detected

#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    CallForHeat();
}

void CallForHeat()
{
    if (P4IN & BIT1) {
        // System Steps Here
    }
    else {
        // IDLE STATE
    }
    return;
}