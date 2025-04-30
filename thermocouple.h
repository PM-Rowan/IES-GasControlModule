#ifndef MSP430FR2355_THERMOCOUPLE_H
#define MSP430FR2355_THERMOCOUPLE_H


// Thermocouple pin definition
#define THERMOCOUPLE_PIN BIT3  // Thermocouple connected to P1.3 (ADC channel A3)

// Temperature threshold for alert
#define DESIRED_TEMP 75  // Example: Desired temperature threshold in °C

// Function prototypes
void setup();                 // Function to configure peripherals
int readThermocoupleTemp(); 
  // Function to read thermocouple temperature

bool isFlameDetected(int temperature, int flameThreshold);
#endif // MSP430FR2355_THERMOCOUPLE_H