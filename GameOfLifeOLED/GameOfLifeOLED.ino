#include "Life.h"
#include <RF24.h>

RF24 radio(7, 8);
const byte nodeAddress[5] = {'N','O','D','E','%'};
boolean resetScreen = false; 

int globalSeed = 0; 

/* SLboat Add Device */
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED 

Life game; 
void setup() {
  // Initialize display. 
  u8g.begin();

  // Initialize radio
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(0, nodeAddress);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  // Calculate a seed based on nodeAddress
  for (int i = 0; i < 5; i++) {
    globalSeed += (int) nodeAddress[i];
  }
  
  // put your setup code here, to run once:
  game.init(&u8g, globalSeed);
}

void loop() {
  if (radio.available()) {
    uint8_t payloadSize = radio.getDynamicPayloadSize(); 
    char payload[payloadSize] = "";
    radio.read(payload, sizeof(payload));
    resetScreen = true; 
    // Whatever the incoming payload is there, use it as the seed 
    game.init(&u8g, atoi(payload));
  }
  
  // Picture loop. 
  u8g.firstPage();
  do {
    if (resetScreen) {
      u8g.setHiColor(1);
      u8g.drawBox(0, 0, 128, 64);
    } else {
      game.draw();
    }
  } while ( u8g.nextPage() );

  // put your main code here, to run repeatedly:
  game.updateScreen();

  if (game.isDone()) {
    game.init(&u8g, globalSeed);
  }

  // Wait a bit before removing that rectangle from the screen. 
  if (resetScreen) {
    delay(300); 
    resetScreen = false; 
  }

  delay(100);
}
