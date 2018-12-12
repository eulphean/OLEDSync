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
boolean hide = true;

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
    if (payloadSize == 2) { // We received a position
      creaturePos[0] = payload[0]; creaturePos[1] = payload[1];
      hide = false;
    } else {
      hide = true; 
    }
  }

  // Picture loop. 
  u8g.firstPage();
  do {
    if (!hide) {
      uint8_t a = creaturePos[0] * (cellWidth); 
      uint8_t b = creaturePos[1] * (cellWidth); 
//      u8g.setHiColor(1);
//      u8g.drawBox(a, b, cellWidth, cellWidth);
      drawCreature(a, b);
    }
  } while ( u8g.nextPage() );
  
}

void drawCreature(uint8_t startX, uint8_t startY) {
  uint8_t faceWidth = 18;
  uint8_t faceHeight = 8; 
  // Draw a 16x16 frame
  u8g.setHiColor(1);

  // Left block
  u8g.drawBox(startX, startY + 2, 2, 8); 

  // Right block
  u8g.drawBox(startX+20, startY + 2, 2, faceHeight);
  
  // Top block
  u8g.drawBox(startX + 2, startY, faceWidth, 2);
  
  // Bottom block
  u8g.drawBox(startX + 2, startY + faceHeight, faceWidth, 2);
  
  // Left eye
  u8g.drawDisc(startX + 6, startY + 4, 1);
  // Right eye
  u8g.drawDisc(startX + 15, startY + 4, 1);

  // Neck
  u8g.drawBox(startX + 6, startY + faceHeight + 2, 10, 2);

  // Torso
  u8g.drawFrame(startX + 2, startY + faceHeight+4, faceWidth, 6);

  // Legs
  u8g.drawBox(startX + 4, startY + faceHeight + 10, 2, 2 );
  u8g.drawBox(startX + faceWidth - 2, startY + faceHeight + 10, 2, 2);
}

