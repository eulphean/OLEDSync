#include <U8g2lib.h>
#include <RF24.h>
#include <Block.h>

/* SLboat Add Device */
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED

const uint8_t screenWidth = 128; 
const uint8_t screenHeight = 64;
const uint8_t *cur = "00002"; 
const uint8_t *next = "00003";

// Block that will be moving here and there. 
Block block; 
Radio radio; 
bool shouldUpdateBlock = false; 

void setup(void) {
  Serial.begin(9600);
  initOLED(); 
  radio.init(cur, next); 
  radio.enableReceiver(); 
  // Don't init the block because it doesn't exist right now. 
}

void draw() {
  block.show(&u8g2);
}

void updateBlock() {
  // Update block
  block.updateBlock(&radio);
  if (!block.exists) {
    radio.enableTransmitter();
    radio.sendMsg(block.getPosY());
    radio.enableReceiver();
    shouldUpdateBlock = false;
  }
}

void updateRadio() {
  // Update radio
  char msg = radio.updateForReceive();
  if (msg != '-') {
    // Process this message.
    int posY = (int) msg;
    block.init(0, posY);
    shouldUpdateBlock = true;
  }
}

void loop(void) {
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );

  if (shouldUpdateBlock) {
    updateBlock(); 
  }
  updateRadio(); 
}

void initOLED() {
  u8g2.begin();
  u8g2.clearDisplay(); 
  u8g2.clearBuffer(); 
}



