/*
 * Simple test transmitter program that transmits 
 * Hello and then World in a loop. This should be
 * used for testing all the systems. 
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
char text[32]; // Index for the receiver. 

// OLED initialize
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // OLED state. 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer
}

void loop() {
  char textA[] = "Hello"; 
  radio.write(&textA, sizeof(textA));
  showText(textA);
  delay(1000);
  
  char textB[] = "World";
  radio.write(&textB, sizeof(textB));
  showText(textB);
  delay(1000);
}

void showText(char* string) {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println(string);
  display.display();
}

