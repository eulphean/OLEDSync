/*
 *  Simple example to print Morse code on an OLED screen. 
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include "Morse.h"

// Radio
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// OLED initialize
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

// Morse Initialize
Morse morseEncoder(&radio);

// Serial variables. 
String inputText = ""; // Holds the text from Serial
byte inputTextLength; // Length of the text

void setup()
{
  // Initialize Serial. 
  Serial.begin(9600);

  // Initialize the transmitting radio.
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  // Initialize the OLED.
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(BLACK, WHITE);
  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer
}

void loop()
{
  // This becomes true when we start typing into the serial input. 
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputText += inChar; 
    if (inChar == "\n") {
      Serial.println(inputText);
      
    }
  }

  
  // Read string from Serial monitor 
  // Convert the string into Morse code.Print the code on the OLED.
}

//  showTextOneByOne("New Message", 11);
//  delay(2000);
//  dot(); dot(); dot(); // S
//  dash(); dash(); dash(); // O
//  dot(); dot(); dot(); // S
//  showTextOneByOne("SOS", 3);
//  delay(2000);
//void dot()
//{
//  display.clearDisplay();
//  display.fillRoundRect(30, 0, 70, display.height(), 30, WHITE);
//  display.display();
//  delay(300);
//  display.clearDisplay();
//  display.display();
//  delay(300);
//}
//
//void dash()
//{
//  display.clearDisplay();
//  display.fillRect(0, 0, display.width(), display.height(), WHITE);
//  display.display();
//  delay(1200);
//  display.clearDisplay();
//  display.display();
//  delay(300);
//}
//
//void showText(char* string) {
//  display.clearDisplay();
//  display.print(string);
//  display.display();
//}
//
//void showTextOneByOne(char * string, int length) {
//  display.setCursor(0,0);
//  // One by one print out obsession. 
//  for (int i = 0; i < length; i++) {
//    char curChar = string[i]; 
//    display.print(curChar);
//    display.display();
//    delay(100);
//  }
//}
