/*
 * Morse Receiver code. This will be the receiving Arduinos connected
 * to OLEDs that will receive the radio signals. 
 */
#include <RF24.h>
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
  radio.setAutoAck(false);
  radio.enableDynamicPayloads();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();   // clears the screen and buffer
  display.display(); // show splashscreen
}
void loop() {
  if (radio.available()) {
    int payloadSize = radio.getDynamicPayloadSize(); 
    char payload[payloadSize] = ""; 
    radio.read(payload, sizeof(payload));

    if (payloadSize > 1) {
      showStringOneByOne(payload, payloadSize); 
    } else {
      switch (payload[0]) {
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
      }// End switch
    }// End else
  }// End Radio
}// End function

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
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);

  // Text to show. 
  char t[3] = "NEW"; 
  display.setCursor(50, 10); 
  for (int i = 0; i < 3; i++) {
    char c = t[i];
    display.print(c); 
    display.display();
    delay(150);
  }
  
  char n[7] = "MESSAGE";
  display.setCursor(25, 28); 
  for (int i = 0; i < 7; i++) {
    char c = n[i]; 
    display.print(c); 
    display.display();
    delay(150);
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

void showStringOneByOne(char payload [], int payloadSize) {
  display.clearDisplay(); 
  display.setCursor(0, 0); 
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE); 

  // We don't want to print the endline character. 
  for (int i = 0; i < payloadSize-1; i++) {
    char curChar = payload[i]; 
    display.print(curChar);
    display.display(); 
    delay(200);
  }
}


