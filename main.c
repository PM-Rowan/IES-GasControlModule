// Board Libraries
#include "msp430fr2355.h"
#include <msp430.h>

// Custom Libraries
#include "CallForHeat-Interrupt.h"
#include "RGB_LED.h"

void systemSetup();

void main(void)
{
    systemSetup();


    
}

void systemSetup()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    
    CallForHeat_init(); // Setup Call For Heat Signal
}