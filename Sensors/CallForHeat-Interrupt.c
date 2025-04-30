#include "intrinsics.h"
#include "msp430fr2355.h"
#include <msp430.h>

void CallForHeat();

void CallForHeat_init(void)
{
    P3DIR &= ~BIT1; // P3.0 button is input
    P3REN |= BIT0; // Enable Resistor
    P3OUT |= BIT0; // Pull-up
    P3IES |= BIT0; // H to L

    P3IE |= BIT0; // enables IRQ 
    P3IFG &= ~BIT0; 
}

// Interrupt when Logical "HIGH" (1) is detected

#pragma vector = PORT3_VECTOR
__interrupt void ISR_Port3(void)
{
    CallForHeat();
}

void CallForHeat()
{
    if (P3IN & BIT0) {
        // System Steps Here
    }
    else {
        // IDLE STATE
    }
    
    P3IFG &= ~BIT0; // Turn off flag
}