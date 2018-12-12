#include <RF24.h>

// Radio to send coordinates. 
RF24 radio (7,8);

uint8_t posIdx = 0; 
uint8_t pos[2];

const byte nodeAddress[5] = {'N','O','D','E','0'};

// Global string to read the serial data. 
String s; 

void setup() {
  Serial.begin(9600); 
  Serial.println("Arduino Ready.");
  
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openWritingPipe(nodeAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  
}

void serialEvent() {
  while(Serial.available()) {
    char inChar = Serial.read(); 
    if (inChar == ',') {
      // Extract xPos
      pos[posIdx] = s.toInt();
      posIdx++;
      
      // Reset string
      s = "";
    } else if (inChar == '.') {
      // Extract yPos
      pos[posIdx] = s.toInt(); 
      transmitData();
      
      // Reset index and string
      posIdx = 0; 
      s = "";
    } else {
      
      // Keep appending to the string. 
      s += inChar; 
    }
  }
}

void transmitData() {
  radio.openWritingPipe(nodeAddress);
  radio.write(&pos, sizeof(pos));
}

