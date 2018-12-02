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
  sig = '.'; 
  _radio->write(&sig, sizeof(sig));
  delay(300);

  // Dot off
  sig = 'x'; 
  _radio->write(&sig, sizeof(sig));
  delay(300);
}

// Transmit dash
void Morse::dash() {
  char sig; 

  // Dash. 
  sig = '-'; 
  _radio->write(&sig, sizeof(sig));
  delay(1200);

  // Dash off.
  sig = 'x'; 
  _radio->write(&sig, sizeof(sig));
  delay(300);
}
 
void Morse::newMessage() {
  char sig; 

  // New message
  sig = 'n'; 
  _radio->write(&sig, sizeof(sig)); 
  delay(4000); 
}
void Morse::process(String text, int stringLength) {
  // New message notification. 
  newMessage();

  // Go through each character in the string. 
  // Get the corresponding Morse Code pattern for each character.
  // Transmit the morse code for that character. 
  for (int i = 0; i < stringLength; i++) {
     char curChar = text[i];
     transmitCode(curChar);
  }

  // Actual message to the receiver.  
  
}

void Morse::transmitCode(char ch) {
  switch (ch) {
    case 'a':
    case 'A': {
      dot(); dash();
      break; 
    }

    case 'b':
    case 'B': {
      dash(); dot(); dot(); dot();
      break; 
    }

    case 'c':
    case 'C': {
      dot(); dot(); dash(); dot();
      break; 
    }

    case 'd':
    case 'D': {
      dash(); dot(); dot();
      break; 
    }

    case 'e':
    case 'E': {
      dot();
      break; 
    }

    case 'f':
    case 'F': {
      dot(); dot(); dash(); dot();
      break; 
    }

    case 'g':
    case 'G': {
      dash(); dash(); dot();
      break; 
    }

    case 'h':
    case 'H': {
      dot(); dot(); dot(); dot();
      break; 
    }

    case 'i':
    case 'I': {
      dot(); dot();
      break; 
    }

    case 'j':
    case 'J': {
      dot(); dash(); dash(); dash();
      break; 
    }

    case 'k':
    case 'K': {
      dash(); dot(); dash();
      break; 
    }

    case 'l':
    case 'L': {
      dot(); dash(); dot(); dot();
      break; 
    }

    case 'm':
    case 'M': {
      dash(); dash();
      break; 
    }

    case 'n':
    case 'N': {
      dash(); dot();
      break; 
    }

    case 'o':
    case 'O': {
      dash(); dash(); dash();
      break; 
    }

    case 'p':
    case 'P': {
      dot(); dash(); dash(); dot();
      break; 
    }

    case 'q':
    case 'Q': {
      dash(); dash(); dot(); dash();
      break; 
    }

    case 'r':
    case 'R': {
      dot(); dash(); dot();
      break; 
    }

    
    case 's':
    case 'S': {
      dot(); dot(); dot();
      break; 
    }

    case 't':
    case 'T': {
      dash();
      break; 
    }

    case 'u':
    case 'U': {
      dot(); dot(); dash();
      break; 
    }

    
    case 'v':
    case 'V': {
      dot(); dot(); dot(); dash();
      break; 
    }

    case 'w':
    case 'W': {
      dot(); dash(); dash();
      break; 
    }

    case 'x':
    case 'X': {
      dash(); dot(); dot(); dash();
      break; 
    }

    
    case 'y':
    case 'Y': {
      dash(); dot(); dash(); dash();
      break; 
    }

    case 'z':
    case 'Z': {
      dash(); dash(); dot(); dot();
      break; 
    }

    default: 
      break;
    
  }
}

