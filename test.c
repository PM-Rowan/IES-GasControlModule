#include "pilotLightTimer.h"
#include "intrinsics.h"
#include "msp430fr2355.h"

void system_init();
void wait();

void main()
{
    system_init();

    Indicator_init();

    Indicate();

    pilotLightTimer_init();
    pilotLightTimer_start();

    Indicate();

    return;
}

void wait()
{
    __delay_cycles(500000); // 0.5s
}

void Indicator_init()
{
    P1DIR |= BIT0;
}

void Indicate()
{
    P1DIR ^= BIT0;
}

void system_init()
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    return;
}