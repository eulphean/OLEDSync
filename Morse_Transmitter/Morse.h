/*
  Morse.h - Library for encoding a string into Morse code.
  Created by Amay Kataria on December 2, 2018
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

class Morse
{
  public:
    // Initialize with a radio object to transmit signals for dits/dahs
    Morse(RF24 * radio);

    // Send an input string to convert into Morse code and transmit. 
    void process(String text, int stringLength); 

  private:
    void newMessage();
    void dot(); 
    void dash();
    void transmitCode(char ch);
    RF24 * _radio; 
};

#endif
