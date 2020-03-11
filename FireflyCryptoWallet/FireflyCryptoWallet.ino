// Fingerprint image. 
#include "Fingerprints.h"

// Our custom zero-memory display driver
#include "firefly_display.h"

// Execution begins here
void setup() {
    // Initialize the I2C OLED display
    display_init(1234);

    // Show the hour-glass waiting screen
    display_hourglass();
}


void loop() {
    // Never entered
}
