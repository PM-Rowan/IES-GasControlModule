#define mainGasValve

volatile unsigned char valveOpenDegrees = 0; // Dictates Angle of Main Valve Servo

void setServoAngle(char);