#include "msp430fr2355.h"

// FRS - Flame Restart System

void FRS_pilotLightFail()
{
    // close Pilot Solenoid
    // wait/do other
}

void FRS_flameLost()
{
    // close Gas Servo
    FRS_pilotLightFail();
}