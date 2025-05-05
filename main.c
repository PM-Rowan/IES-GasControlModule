// Board Libraries
#include "msp430fr2355.h"
#include <msp430.h>

// Custom Libraries //

// // Global Vars
#include "GLOBAL.h" 

// // Inputs
#include "Headers/Inputs/CallForHeat-Interrupt.h"
#include "Headers/Inputs/potentiometer.h"
#include "Headers/Inputs/Sensors.h"
#include "Headers/Inputs/thermocouple.h"

// // Internal
#include "Headers/Internal/FRS.h"
#include "Headers/Internal/pilotLightTimer.h"

// // Outputs
#include "Headers/Outputs/ignitor.h"
#include "Headers/Outputs/RGB_LED.h"
#include "Headers/Outputs/mainGasValve.h"
#include "Headers/Outputs/pilotGasVavle.h"

// Main Sub-Function Declaration
void systemSetup();


// The Meat and Potatoes
void main(void)
{
    systemSetup();

    while(1) {
        // Let the 'magic' happen
    }
}

// Main Sub-Functions
void systemSetup()
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    // SYSTEM INITS GO HERE
    
    // // Input INITS
        CallForHeat_init();
        potentiometer_init();
        adc_Init();
        thermocouple_init();
        // thermistor_init();

    // // Internal INITS
        pilotLightTimer_init();

    // // Output INITS
        ignitor_init();
        RGB_init();

    // RUN VERY LAST!!!
    __enable_interrupt();
}