#include <RF24.h>

// Radio to send coordinates. 
RF24 radio (7,8);

uint8_t posIdx = 0; 
uint8_t pos[4];

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

// Global string to read the serial data. 
String s; 

void setup() {
  Serial.begin(9600); 
  Serial.println("Arduino Ready.");
  
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  
}

void serialEvent() {
  while(Serial.available()) {
    char inChar = Serial.read(); 
    if (inChar == ',') {
      // Extract info.
      pos[posIdx] = s.toInt();
      posIdx++;
      
      // Reset string
      s = "";
    } else if (inChar == '.') {
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
  // Debug string. 
//  Serial.print("Pos val: "); Serial.print(pos[0]); 
//  Serial.print(","); Serial.print(pos[1]); Serial.print(",");
//  Serial.print(pos[2]); Serial.print(","); Serial.println(pos[3]);
  
  // Only send xPos, yPos to the receiver. 
  uint8_t creaturePos [2] = { pos[1], pos[2] };
  radio.openWritingPipe(nodeAddresses[pos[0]]);
  radio.write(&creaturePos, sizeof(creaturePos));

  // Check if there is a previous screen as well. 
  // Some arbitrary large number that's sent as default.
  if (pos[3] != 100) {
    char sig = 'x'; // Symbol to tell the previous screen that this creature 
    // has left. Ideally, I'll send the index and the action to the screen
    // to tell what to do. Every creature should have some sort of an index
    // in this ecosystem. 
    radio.openWritingPipe(nodeAddresses[pos[3]]); 
    radio.write(&sig, sizeof(sig));
  }
}

