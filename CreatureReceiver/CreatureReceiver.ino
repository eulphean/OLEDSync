#include <RF24.h>
#include "U8glib.h"

RF24 radio(7,8);
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  
const byte nodeAddress[5] = {'N','O','D','E','0'};
const uint8_t numRows = 8; 
const uint8_t numCols = 16; 
const uint8_t cellWidth = 8; 

// Global creature position.
uint8_t creaturePos[2];

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  u8g.begin();
  u8g.setRot90();

  // Initialize radio.
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(0, nodeAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // Is radio available
  if (radio.available()) {
    uint8_t payloadSize = radio.getDynamicPayloadSize(); 
    uint8_t payload[payloadSize];
    radio.read(payload, sizeof(payload));
    creaturePos[0] = payload[0]; creaturePos[1] = payload[1];
  }

  // Picture loop. 
  u8g.firstPage();
  do {
    uint8_t a = creaturePos[0] * (cellWidth); 
    uint8_t b = creaturePos[1] * (cellWidth); 
    u8g.setHiColor(1);
    u8g.drawBox(a, b, cellWidth, cellWidth);
  } while ( u8g.nextPage() );
  
}
