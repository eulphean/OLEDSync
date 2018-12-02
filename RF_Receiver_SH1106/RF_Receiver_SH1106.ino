
/*
 *  Test receiver program to show the received text on  
 *  SSH1106 1.3" Blue OLED. 
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// OLED setup.
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0, 0);
  display.fillRect(0, 0, display.width(), display.height(), WHITE);
  display.display(); // show splashscreen
}
void loop() {
  if (radio.available()) {
    char string[32] = ""; 
    radio.read(&string, sizeof(string));
    showText(string);
  }
}

void showText(char* string) {
//  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
//  display.setCursor(10, 10);
  display.print(string);
  display.display();
}

