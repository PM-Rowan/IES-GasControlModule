#ifndef RGB_LED
#define RGB_LED

void RGB_init();
void RGB_PWM(char, char, char);

// Light Value // range: [0,255]
const unsigned char rgbLevel = 127;

// Preset Functions
#define TOOHOT RGB_PWM(rgbLevel, 0, 0);             // Main Temp Too Hot
#define INTEMP RGB_PWM(0, rgbLevel, 0);             // Main Temp Nominal
#define TOOCOLD RGB_PWM(0, 0, rgbLevel);            // Main Temp Too Cold

#define RG RGB_PWM(rgbLevel, rgbLevel, 0);          // unutilized
#define RB RGB_PWM(rgbLevel, 0, rgbLevel);          // unutilized
#define GB RGB_PWM(0, rgbLevel, rgbLevel);          // IDLE State

#define WH RGB_PWM(rgbLevel, rgbLevel, rgbLevel);   // CallForHeat State
#define OFF RGB_PWM(0, 0, 0);                       // OFF (Default)

#endif