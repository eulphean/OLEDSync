#include "U8glib.h"

/* SLboat Add Device */
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); // I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED 

uint8_t startX = 0; 
uint8_t startY = 20; 
uint8_t faceWidth = 18;
uint8_t faceHeight = 8;  

uint8_t moveX = 0; uint8_t moveY = 0; 
void setup() {
  u8g.begin();
}

void loop(void) {
  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  delay (200);
  moveX++;
}

void draw() { 
  // Draw a 16x16 frame
  u8g.setHiColor(1);

  // Left block
  u8g.drawBox(startX + moveX, startY + 2, 2, 8); 

  // Right block
  u8g.drawBox(startX+20 + moveX, startY + 2, 2, faceHeight);
  
  // Top block
  u8g.drawBox(startX + 2 + moveX, startY, faceWidth, 2);
  
  // Bottom block
  u8g.drawBox(startX + 2 + moveX, startY + faceHeight, faceWidth, 2);
  
  // Left eye
  u8g.drawDisc(startX + 6 + moveX, startY + 4, 1);
  // Right eye
  u8g.drawDisc(startX + 15 + moveX, startY + 4, 1);

  // Neck
  u8g.drawBox(startX + 6 + moveX, startY + faceHeight + 2, 10, 2);

  // Torso
  u8g.drawFrame(startX + 2 + moveX, startY + faceHeight+4, faceWidth, 6);

  // Legs
  u8g.drawBox(startX + 4 + moveX, startY + faceHeight + 10, 2, 2 );
  u8g.drawBox(startX + faceWidth - 2 + moveX, startY + faceHeight + 10, 2, 2);
}

