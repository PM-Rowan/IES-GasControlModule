#define thermocouple


// Thermocouple pin definition
#define THERMOCOUPLE_PIN BIT3  // Thermocouple connected to P1.3 (ADC channel A3)

// Temperature threshold for alert
#define DESIRED_TEMP 75 // Desired temperature threshold in °C

// Function prototypes
void thermocouple_init();     // Function to configure peripheral pins
int readThermocoupleTemp();   // Function to read thermocouple temperature

bool isFlameDetected(int temperature, int flameThreshold);