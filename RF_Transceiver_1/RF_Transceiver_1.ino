#include "Bitmaps.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
char rxIdx; // Index for the receiver. 

// OLED initialize
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // OLED state. 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer
}
void loop() {
  // Pattern 1
  // Turn On, Turn off your self, then send 1->0, then 2->0, then 3->0, 4->0. 5->0
 
  // Transceiver OLED. 
  display.drawBitmap(0, 0, head, 128, 64, 1); 
  display.display(); 

  delay(500); 
  
  display.drawBitmap(0, 0, head, 128, 64, 0); 
  display.display();

  // Receiver 1 OLED (On)
  rxIdx = '1'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  delay(500);

  // Receiver 1 OLED (Off)
  rxIdx = '0'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  // Receiver 2 OLED (On)
  rxIdx = '2'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  delay(500);

  // Receiver 1 OLED (Off)
  rxIdx = '0'; 
  radio.write(&rxIdx, sizeof(rxIdx));
  
  // Receiver 3 OLED (On)
  rxIdx = '3'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  delay(500);

  // Receiver 3 OLED (Off)
  rxIdx = '0'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  // Receiver 4 OLED (On)
  rxIdx = '4'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  delay(500);

  // Receiver 4 OLED (Off)
  rxIdx = '0'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  delay(500);

  // All On, 
  // Tx OLED
  display.drawBitmap(0, 0, head, 128, 64, 1); 
  display.display(); 
  // RX OLEDs
  rxIdx = '5'; 
  radio.write(&rxIdx, sizeof(rxIdx));

  delay(20000);

//  for (int i = 0; i < 10; i++) {
//
//  
//    delay(500); 
//  
//    // All Off
//    // Tx OLED
//    display.drawBitmap(0, 0, head, 128, 64, 0); 
//    display.display();
//    // RX OLEDs
//    rxIdx = '0'; 
//    radio.write(&rxIdx, sizeof(rxIdx));
//  }
}
