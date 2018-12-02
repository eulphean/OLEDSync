/*
 *  Simple example to print Morse code on an OLED screen. 
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// OLED initialize
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

void setup()
{
  // OLED state. 
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.setTextSize(2);
  display.setCursor(0,0);
  display.setTextColor(BLACK, WHITE);
  display.display(); // show splashscreen
  display.clearDisplay();   // clears the screen and buffer
}

void loop()
{
  showTextOneByOne("SOS", 3);
  delay(2000);
  dot(); dot(); dot(); // S
  dash(); dash(); dash(); // O
  dot(); dot(); dot(); // S
  showTextOneByOne("SOS", 3);
  delay(2000);
}

void dot()
{
  display.clearDisplay();
  display.fillRoundRect(30, 0, 70, display.height(), 30, WHITE);
  display.display();
  delay(300);
  display.clearDisplay();
  display.display();
  delay(300);
}

void dash()
{
  display.clearDisplay();
  display.fillRect(0, 0, display.width(), display.height(), WHITE);
  display.display();
  delay(1200);
  display.clearDisplay();
  display.display();
  delay(300);
}

void showText(char* string) {
  display.clearDisplay();
  display.print(string);
  display.display();
}

void showTextOneByOne(char * string, int length) {
  display.setCursor(0,0);
  // One by one print out obsession. 
  for (int i = 0; i < length; i++) {
    char curChar = string[i]; 
    display.print(curChar);
    display.display();
    delay(100);
  }
}
