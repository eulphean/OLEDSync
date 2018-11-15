#include "Bitmaps.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// OLED setup.
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer

}
void loop() {
  if (radio.available()) {
    char rxIdx; 
    radio.read(&rxIdx, sizeof(rxIdx));
    if (rxIdx == '3' || rxIdx == '5') {
       display.drawBitmap(0, 0, laugh, 128, 64, 1); 
       display.display(); 
    }

    if (rxIdx == '0') {
      display.drawBitmap(0, 0, laugh, 128, 64, 0); 
      display.display();
    }
  }
}

void showText(char* string) {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println(string);
  display.display();
}

