#include "Arduino.h"
#include "Morse.h"

// Constructor implementation.
Morse::Morse(RF24 * radio)
{
    // Assign the radio object. 
    _radio = radio;
}

void Morse::loiter() {
  char sig = '+';

  // Light up left to right
  for (int node=0; node < 12; node++) {
    _radio->openWritingPipe(nodeAddresses[node]); 
    _radio->write(&sig, sizeof(sig));

    delay(200);
  }

  delay(1000);

  sig = 'x';
  // Light down right to left
   for (int node=11; node >= 0; node--) {
    _radio->openWritingPipe(nodeAddresses[node]); 
    _radio->write(&sig, sizeof(sig));

    delay(200);
  }
  
  delay(500);
}

// Transmit dot
void Morse::dot() {
  char sig; 
  
  // Dot
  sig = '.'; 
  sendMultipleAddresses(&sig, sizeof(sig));
  delay(DOT);

  // Dot off
  sig = 'x'; 
  sendMultipleAddresses(&sig, sizeof(sig));
  delay(INNER_PAUSE);
}

// Transmit dash
void Morse::dash() {
  char sig; 

  // Dash. 
  sig = '-'; 
  sendMultipleAddresses(&sig, sizeof(sig));
  delay(DASH);

  // Dash off.
  sig = 'x'; 
  sendMultipleAddresses(&sig, sizeof(sig));
  delay(INNER_PAUSE);
}
 
void Morse::newMessage() {
  char sig; 

  // New message
  sig = 'n'; 
  sendMultipleAddresses(&sig, sizeof(sig));
  
  delay(NEW_MESSAGE); 
}

void Morse::charBreak() {
  char sig; 

  sig = '|';
  sendMultipleAddresses(&sig, sizeof(sig)); 
  delay(CHAR_BREAK);

  // Char break off.
  sig = 'x='; 
  sendMultipleAddresses(&sig, sizeof(sig));
  delay(INNER_PAUSE);
}

void Morse::wordBreak() {
  char sig; 

  sig = '/';
  sendMultipleAddresses(&sig, sizeof(sig));
  delay(WORD_BREAK); 
}

void Morse::sendMessage(String text, int stringLength) {
  char buf[stringLength+1];  
  text.toCharArray(buf, stringLength+1);

  // Number of transmisssions (32 bytes/packet)
  float numTrans = (stringLength+1)/32.0; 
  numTrans = ceil(numTrans); // We need the max number for this division.  

  if (numTrans == 1) {
     sendMultipleAddresses(buf, sizeof(buf));
  } else {
     int totalBytes = stringLength+1; 
     for (int i = 0; i < numTrans; i++) {
        int numBytes = (i==0) ? 32 : totalBytes - i*32;  
        int startIdx = i*32; int endIdx = startIdx + numBytes;
        text.substring(startIdx, endIdx).toCharArray(buf, numBytes); 
        _radio->setPayloadSize(numBytes);
        sendMultipleAddresses(buf, numBytes);
     }
  }
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

  // Transmit string.
  sendMessage(text, stringLength);
}

void Morse::transmitCode(char ch) {
  switch (ch) {
    case ' ': {
      // Word gap. 
      wordBreak();
      break; 
    }
    
    case 'a':
    case 'A': {
      dot(); dash(); charBreak();
      break; 
    }

    case 'b':
    case 'B': {
      dash(); dot(); dot(); dot(); charBreak();
      break; 
    }

    case 'c':
    case 'C': {
      dot(); dot(); dash(); dot(); charBreak();
      break; 
    }

    case 'd':
    case 'D': {
      dash(); dot(); dot(); charBreak();
      break; 
    }

    case 'e':
    case 'E': {
      dot(); charBreak();
      break; 
    }

    case 'f':
    case 'F': {
      dot(); dot(); dash(); dot(); charBreak();
      break; 
    }

    case 'g':
    case 'G': {
      dash(); dash(); dot(); charBreak();
      break; 
    }

    case 'h':
    case 'H': {
      dot(); dot(); dot(); dot(); charBreak();
      break; 
    }

    case 'i':
    case 'I': {
      dot(); dot(); charBreak();
      break; 
    }

    case 'j':
    case 'J': {
      dot(); dash(); dash(); dash(); charBreak();
      break; 
    }

    case 'k':
    case 'K': {
      dash(); dot(); dash(); charBreak();
      break; 
    }

    case 'l':
    case 'L': {
      dot(); dash(); dot(); dot(); charBreak();
      break; 
    }

    case 'm':
    case 'M': {
      dash(); dash(); charBreak();
      break; 
    }

    case 'n':
    case 'N': {
      dash(); dot(); charBreak();
      break; 
    }

    case 'o':
    case 'O': {
      dash(); dash(); dash(); charBreak();
      break; 
    }

    case 'p':
    case 'P': {
      dot(); dash(); dash(); dot(); charBreak();
      break; 
    }

    case 'q':
    case 'Q': {
      dash(); dash(); dot(); dash(); charBreak();
      break; 
    }

    case 'r':
    case 'R': {
      dot(); dash(); dot(); charBreak();
      break; 
    }

    
    case 's':
    case 'S': {
      dot(); dot(); dot(); charBreak();
      break; 
    }

    case 't':
    case 'T': {
      dash(); charBreak();
      break; 
    }

    case 'u':
    case 'U': {
      dot(); dot(); dash(); charBreak();
      break; 
    }

    
    case 'v':
    case 'V': {
      dot(); dot(); dot(); dash(); charBreak();
      break; 
    }

    case 'w':
    case 'W': {
      dot(); dash(); dash(); charBreak();
      break; 
    }

    case 'x':
    case 'X': {
      dash(); dot(); dot(); dash(); charBreak();
      break; 
    }

    
    case 'y':
    case 'Y': {
      dash(); dot(); dash(); dash(); charBreak();
      break; 
    }

    case 'z':
    case 'Z': {
      dash(); dash(); dot(); dot(); charBreak();
      break; 
    }

    case '0': {
      dash(); dash(); dash(); dash(); dash(); charBreak();
      break;
    }

    case '1': {
      dot(); dash(); dash(); dash(); dash(); charBreak();
      break;
    }

    case '2': {
      dot(); dot(); dash(); dash(); dash(); charBreak();
      break;
    }

    case '3': {
      dot(); dot(); dot(); dash(); dash(); charBreak();
      break;
    }

    case '4': {
      dot(); dot(); dot(); dot(); dash(); charBreak();
      break;
    }

    case '5': {
      dot(); dot(); dot(); dot(); dot(); charBreak();
      break;
    }

    case '6': {
      dash(); dot(); dot(); dot(); dot(); charBreak();
      break;
    }

    case '7': {
      dash(); dash(); dot(); dot(); dot(); charBreak();
      break;
    }

    case '8': {
      dash(); dash(); dash(); dot(); dot(); charBreak();
      break;
    }

    case '9': {
      dash(); dash(); dash(); dash(); dot(); charBreak();
      break;
    }

    default: 
      break;
    
  }
}

void Morse::sendMultipleAddresses(char * buf, int len) {
  for (byte node=0; node < 12; node++) {
    _radio->openWritingPipe(nodeAddresses[node]); 
    _radio->write(buf, len);
  }
}

