#include "Arduino.h"
#include "Morse.h"

// Constructor implementation.
Morse::Morse(RF24 * radio)
{
    // Assign the radio object. 
    _radio = radio;
}

// Transmit dot
void Morse::dot() {
  char sig; 

  // Dot
  sig = "."; 
  _radio->write(&sig, sizeof(sig));
  delay(300);

  // Dot off
  sig = "x"; 
  _radio->write(&sig, sizeof(sig));
  delay(300);
}

// Transmit dash
void Morse::dash() {
  char sig; 

  // Dash. 
  sig = "-"; 
  _radio->write(&sig, sizeof(sig));
  delay(1200);

  // Dash off.
  sig = "x"; 
  _radio->write(&sig, sizeof(sig));
  delay(300);
}

void Morse::emit(char * string) {
  // Go through each character in the string. 
  // Get the corresponding Morse Code pattern for each character.
  // Transmit the morse code for that character. 
}

