#include "msp430fr2355.h"

// Custom Libraries
#include "Headers/Internal/pilotLightTimer.h"

#include "Headers/Outputs/mainGasValve.h"
#include "Headers/Outputs/pilotGasValve.h"

// FRS - Flame Restart System

void FRS_pilotLightFail()
{
    pilotGasValve_close();
    pilotLightTimer_start(); // Turns off CallForHeat Interrupt (Disables System)
}

void FRS_flameLost()
{
    setServoAngle(0); // Close Main Gas Valve

    FRS_pilotLightFail(); // closes PL valve and begins disabled period
}