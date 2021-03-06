/*
 *  Simple example to print Morse code on an OLED screen. 
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "Morse.h"

// Radio
RF24 radio(7, 8); // CE, CS

// Morse Initialize
Morse morseEncoder(&radio);

// Serial variables. 
String inputText = ""; // Holds the text from Serial
int inputTextLength = 0; // Length of the text

void setup()
{
  // Initialize Serial. 
  Serial.begin(9600);

  // Initialize the transmitting radio.
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.println("Begin");
}

void loop()
{
  // As soon as were write something in the serial port and press enter,
  // Serial.available() > 0. Serial.read() reads off 1 byte from the 
  // Serial buffer. 
  while (Serial.available()) {
    char inChar = Serial.read(); 
    if (inChar == '\n') {
      Serial.print(inputText); Serial.print(", "); Serial.println(inputTextLength);
      morseEncoder.process(inputText, inputTextLength);
      inputText = "";
      inputTextLength = 0; 
      delay(5000);
    } else {
      inputText += inChar; 
      inputTextLength++;
    }
  }

  delay(1000);

  // Loiter for a bit. 
  morseEncoder.loiter();
}
