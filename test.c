#include "RGB_LED.h"
#include "intrinsics.h"
#include "msp430fr2355.h"

void system_init();
void wait();

void main()
{
    system_init();

    RGB_init();

    TOOHOT; wait();
    INTEMP; wait();
    TOOCOLD; wait();
    RG; wait();
    RB; wait();
    GB; wait();
    WH; wait();
    OFF; wait();    

    return;
}

void wait()
{
    __delay_cycles(500000); // 0.5s
}

void system_init()
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    return;
}