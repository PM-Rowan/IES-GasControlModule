#define GLOBAL

// ADC Variables (Sensors.c)
extern volatile int ADC_AX[16] = {}; // All Values will be 12bit in a 16bit int 

// Main Gas Valve Variables (mainGasValve.c)
extern volatile unsigned char valveOpenDegrees; // Dictates Angle of Main Valve Servo [0, 90]
extern volatile unsigned char valveOpen; // used as 8bit unsigned int   [0, 255]