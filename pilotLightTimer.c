#include "msp430fr2355.h"
#include <msp430.h>

void timerDone();

void pilotLightTimer_init() // 128 Second Timer
{
    TB0CCR0 = 0xFFFF - 1; // 16bMAX
    TB0CCTL0 = CCIE;

    TB0CTL |= ID__8; // divide by 8
    TB0EX0 |= BIT2 | BIT1| BIT0; // divide by 8

    TB0CTL |= TBSSEL__ACLK | TBCLR; // use second clock + reset counter
    __enable_interrupt(); 

}

void pilotLightTimer_start()
{
    P3IE &= ~BIT0; // disable CallForHeat Interrupt
    TB0CTL |= MC__UP | TBCLR; // start count up and reset
    TB0CCTL0 |= TBIE; // enable interrupt
}

void timerDone();

#pragma vector = TIMER0_B0_VECTOR //B0_PilotLightTrigger
__interrupt void TB0_pilotLight(void)
{
    timerDone();
}

void timerDone()
{
    P3IE |= BIT0; // enable CallForHeat Interrupt
    TB0CTL |= MC__STOP; // STOP Timer 
    TB0CCTL0 &= ~TBIE; // disable Timer interrupt
}