#include "msp430fr2355.h"
#include <msp430.h>
#include <type_traits>

void RGB_init()
{
    P6DIR |= BIT0 | BIT1 | BIT2;                     // P6.0, P6.1, and P6.2 output
    P6SEL0 |= BIT0 | BIT1 | BIT2;                    // P6.0, P6.1, and P6.2 options select

    PM5CTL0 &= ~LOCKLPM5;

    TB3CCR0 = 1000 - 1;                         // PWM Period

    // CCTL# Mode: reset/set
    // CCR# Default to Off (0)

    TB3CCTL1 = OUTMOD_3;
    TB3CCR1 = 0;

    TB3CCTL2 = OUTMOD_3;
    TB3CCR2 = 0;
    
    TB3CCTL3 = OUTMOD_3;
    TB3CCR3 = 0;

    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;

    return;
}

// char is an 8b/1B that can have values of (0-255)
void RGB_PWM(char R, char G, char B)
{
    TB3CCR1 = R << 2; // R * 4: (0,255) -> (0,1020)
    TB3CCR2 = G << 2; // G * 4: (0,255) -> (0,1020)
    TB3CCR3 = B << 2; // B * 4: (0,255) -> (0,1020)
    return;
}