#ifndef RGB_LED
#define RGB_LED

void RGB_init();
void RGB_PWM(char, char, char);

// Light Value // range: [0,255]
const unsigned char rgbLevel = 127;

// Preset Functions
#define TOOHOT RGB_PWM(rgbLevel, 0, 0);
#define INTEMP RGB_PWM(0, rgbLevel, 0);
#define TOOCOLD RGB_PWM(0, 0, rgbLevel);

#define RG RGB_PWM(rgbLevel, rgbLevel, 0);
#define RB RGB_PWM(rgbLevel, 0, rgbLevel);
#define GB RGB_PWM(0, rgbLevel, rgbLevel);

#define WH RGB_PWM(rgbLevel, rgbLevel, rgbLevel);
#define OFF RGB_PWM(0, 0, 0);

#endif