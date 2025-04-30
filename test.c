#include "intrinsics.h"
#include "msp430fr2355.h"

#include "GLOBAL.h"
#include "Valves/mainGasValve.h"

void system_init();
void wait();

void main()
{
    system_init();

    mainGasValve_init();

    while (1) {

        while(valveOpenDegrees <= 90) {

            //setServoAngle(valveOpenDegrees);
            updateAngle();

            wait();

            valveOpenDegrees += 1;
        }

        valveOpenDegrees = 0;
    }

    return;
}

void wait()
{
    __delay_cycles(250000); // 0.25s
}

void system_init()
{
    WDTCTL = WDTPW | WDTHOLD;
    PM5CTL0 &= ~LOCKLPM5;

    return;
}