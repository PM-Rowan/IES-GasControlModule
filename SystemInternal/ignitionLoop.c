#include "msp430fr2355.h"
#include <msp430.h>

// Custom Libraries
#include "GLOBAL.h"

#include "Headers/Inputs/Sensors.h"
#include "Headers/Inputs/thermocouple.h"

#include "Headers/Internal/FRS.h"

#include "Headers/Outputs/ignitor.h"
#include "Headers/Outputs/mainGasValve.h"
#include "Headers/Outputs/pilotGasValve.h"
#include "Headers/Outputs/RGB_LED.h"

// Header Vars
// #define DESIRED_TEMP 75  // Desired temperature threshold in °C (75°C for testing purposes)
extern volatile unsigned char valveOpenDegrees = 0; // Dictates Angle of Main Valve Servo [0, 90]

// ignitionLoop vars
unsigned int thermocoupleADC = 0;
unsigned int thermistorADC = 0;
unsigned char timesTried = 0;

void ignitionLoop() {

    // runs on the assumption heat is still needed even if there is a fail
    do {

        timesTried += 1;
        
        ignite(); // Spark
        __delay_cycles(100000); // Delay 0.1 seconds
        pilotGasValve_open();
        __delay_cycles(500000); // Delay 0.5 seconds
        deignite();

        thermocoupleADC = readADC(3);

        if (timesTried >= 6) { // fail if tried 6 times
            FRS_pilotLightFail();
            timesTried = 0;
        }

    } while ( (thermocoupleADC <= DESIRED_TEMP));

}

void valveAdjustment() {

    thermistorADC = readADC(4); // Read A4 (P1.4) pin

    if (thermistorADC <= DESIRED_TEMP) {
        valveOpenDegrees += 1;
        TOOCOLD; // RGB LED to Blue
    } 
    else if (thermistorADC <= DESIRED_TEMP) {
        valveOpenDegrees -= 1;
        TOOHOT; // RGB LED to Red
    }
    else {
        INTEMP; // RGB LED to Green
    }

    updateAngle(); // Update Main Gas Valve Angle
    
}