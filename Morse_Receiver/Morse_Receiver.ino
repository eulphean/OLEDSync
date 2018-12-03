/*
 * Morse Receiver code. This will be the receiving Arduinos connected
 * to OLEDs that will receive the radio signals. 
 */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

// OLED setup.
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();   // clears the screen and buffer
  display.display(); // show splashscreen
}
void loop() {
  if (radio.available()) {
    char morse = ""; // . x -
    radio.read(&morse, sizeof(morse));
    switch (morse) {
      case '.': {
        dot(); 
        break; 
      }

      case 'x': {
        clearScreen(); 
        break;
      }

      case '-': {
        dash();
        break;         
      }

      case 'n': {
        newMessage(); 
        break;
      }

      case '|': {
        charBreak();
        break;
      }

      case '/': {
        wordBreak();
        break;
      }

      default: {
        break;
      }
    }
  }
}

void showText(char* string) {
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  display.print(string);
  display.display();
}

void dot()
{
  display.clearDisplay();
  display.fillRoundRect(30, 0, 70, display.height(), 30, WHITE);
  display.display();
}

void dash()
{
  display.clearDisplay();
  display.fillRect(0, 0, display.width(), display.height(), WHITE);
  display.display();
}

void clearScreen() {
  display.clearDisplay();
  display.display();
}

void newMessage() {
  display.clearDisplay(); 
  display.setCursor(0, 0); 
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);

  // Text to show. 
  char text[] = "NEW MESSAGE"; 
  for (int i = 0; i < 11; i++) {
    char curChar = text[i]; 
    display.print(curChar); 
    display.display();
    delay(100);
  }
}

void charBreak() {
  display.clearDisplay(); 
  display.fillRect(display.width()/2-10, 0, 20, display.height(), WHITE); 
  display.display();
}

void wordBreak() {
  display.clearDisplay();
  display.fillTriangle(display.width()/2, 0,
                        display.width()/2-30, display.height(),
                         display.width()/2+30, display.height(), WHITE);
  display.display();
}


