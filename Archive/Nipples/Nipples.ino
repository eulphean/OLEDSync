#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Fingerprints.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

int fingerIdx = 1; // Goes from 1-10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.clearDisplay();   // clears the screen and buffer
}

void loop() {
  // put your main code here, to run repeatedly:
  showFingerprint();
   

   delay(5000);
  // Run the transition, move to the next fingerprint. 
  //drawLines();
}

static void showFingerprint() {
  static unsigned char * finger; 

  switch (fingerIdx) {
     case 1: {
        finger = myBitmap1; 
        break;
     }

     case 2: {
        finger = myBitmap2; 
        break; 
     }

     case 3: {
        finger = myBitmap3; 
        break; 
     }

     case 4: {
        finger = myBitmap4; 
        break; 
     }

     
     case 5: {
        finger = myBitmap5; 
        break; 
     }


     default: {
        finger = myBitmap1; 
        break;
     }
  }
  
  // miniature bitmap display
  display.clearDisplay();
  display.drawBitmap(0, 0, finger, 128, 64, 1);
  display.display(); 

  // Cycle after max fingers implemented. 
  fingerIdx = (fingerIdx+1) % 5; 
}


void drawLines() {
 for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(500);
}

