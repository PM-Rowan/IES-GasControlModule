#include "msp430fr2355.h"
#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    // Put stuff here
}