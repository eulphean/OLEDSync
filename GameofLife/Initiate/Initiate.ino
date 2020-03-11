#include <RF24.h> 

RF24 radio(7, 8);
const byte nodeAddresses[19][5] = {
  {'N','O','D','E','0'},
  {'N','O','D','E','1'},
  {'N','O','D','E','2'},
  {'N','O','D','E','3'},
  {'N','O','D','E','4'},
  {'N','O','D','E','5'},
  {'N','O','D','E','6'},
  {'N','O','D','E','7'},
  {'N','O','D','E','8'},
  {'N','O','D','E','9'},
  {'N','O','D','E','!'},
  {'N','O','D','E','@'},
  {'N','O','D','E','#'},
  {'N','O','D','E','$'},
  {'N','O','D','E','%'},
  {'N','O','D','E','^'},
  {'N','O','D','E','&'},
  {'N','O','D','E','*'},
  {'N','O','D','E','('}
};

// Serial variables. 
String inputText = ""; // Holds the text from Serial
void setup() {
  Serial.begin(9600);
  // Initialize the transmitting radio.
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  Serial.println("Start");
}

void loop() {
  // As soon as we write something in the serial port and press enter,
  // Serial.available() > 0. Serial.read() reads off 1 byte from the 
  // Serial buffer. 
  while (Serial.available()) {
    char inChar = Serial.read(); 
    if (inChar == '\n') {
      Serial.println(inputText);
      uint8_t hash = processText(inputText);
      for (int i = 0; i < 19; i++) {
         radio.openWritingPipe(nodeAddresses[i]);
         radio.write(&hash, sizeof(hash));
      }
      inputText = "";
      delay(5000);
    } else {
      inputText += inChar; 
    }
  }

  delay(1000);
}

// Calculate the hash of this text as a 8 bit number
// Send this number as a seed to game of life. 
uint8_t processText(String inputText) {
  int textLength = inputText.length();
  int sum = 0; 
  for (int i = 0; i < textLength; i++) {
    sum += (int) inputText[i]; 
  }
  return sum/textLength; 
}

