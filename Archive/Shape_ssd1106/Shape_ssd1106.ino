/*********************************************************************
I change the adafruit SSD1306 to SH1106

SH1106 driver don't provide several functions such as scroll commands.

*********************************************************************/

#include <Narcoleptic.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
char* myStrings[]={"Delusion", "Addiction", "Anxiety", "Compulsion", "Habit", "Fetish", "Dependence", "Obsession", "Disorder"};

void setup(){                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  // Clear the buffer.
  display.clearDisplay();

  Narcoleptic.disableTimer1();
  Narcoleptic.disableTimer2();
  Narcoleptic.disableSerial();
  Narcoleptic.disableADC();
//  Narcoleptic.disableWire();
  Narcoleptic.disableSPI();
}


void loop() {
  testfillrect();
//  delay(120000);
    for (int i = 0; i < 10; i++) {
      showObsessionOneByOne();
    }

    // Clear buffer and the screen. 
    display.clearDisplay();
//
//    showObsessionCenter();
//
//    // Wait
//    // delay(2000);
//    Narcoleptic.delay(2000);
//
////    int j = 0;
////    for (int i = 0; i < 99; i++) {
////      display.invertDisplay(true);
////      Narcoleptic.delay(200);
////      display.invertDisplay(false);
////      Narcoleptic.delay(200);
////      if (i % 10 == 0) {
////        char * string = myStrings[j]; 
////        display.setTextSize(random(2, 3)); 
////        display.setTextColor(BLACK, WHITE);
////        display.setCursor(random(0, display.width()), random(0, display.height() - 20));
////        display.print(string);
////        display.display();
////        j++;
////      }
////    }
//
//    display.clearDisplay();
//
//    testfilltriangle();
//
//    Narcoleptic.delay(3000);
//
//    display.clearDisplay();
//
//    iammyownproperty();
//
//    Narcoleptic.delay(3000);
//
//    display.clearDisplay();
}

void showObsessionOneByOne() {
  char obsession[9] = "OBSESSION";

  // Text properties. 
  display.setTextSize(4);
  display.setTextColor(WHITE);
  //display.setCursor(display.width()/2 - 8, display.height()/2 - 12);
  display.setCursor(0, 0);
  // One by one print out obsession. 
  for (int i = 0; i < 9; i++) {
    display.clearDisplay();
    char curChar = obsession[i]; 
    display.print(curChar);
    display.display();
    Narcoleptic.delay(100);
  }
}

void showObsessionCenter() {
  char obsession[9] = "OBSESSION";

  // Text properties. 
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(10, display.height()/2 - 10);
  // One by one print out obsession. 
  for (int i = 0; i < 9; i++) {
    char curChar = obsession[i]; 
    display.print(curChar);
    display.display();
    Narcoleptic.delay(500);
  }
}

void iammyownproperty() {
  char * property = "I AM MY OWN PROPERTY";

  // Text properties. 
  display.setTextSize(2);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0, 0);
  // One by one print out obsession. 
  for (int i = 0; i < 20; i++) {
    char curChar = property[i]; 
    display.print(curChar);
    display.display();
    Narcoleptic.delay(200);
  }
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height(); i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
    Narcoleptic.delay(200);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    Narcoleptic.delay(100);
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}
