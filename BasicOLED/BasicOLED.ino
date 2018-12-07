#include <U8glib.h>
#include <RF24.h>

/* SLboat Add Device */
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED 

uint8_t inc = 0; 
uint8_t mode = 0;

RF24 radio(7, 8); // CE, CSN
const byte nodeAddress[5] = {'N','O','D','E','6'};

class Block {
  public: 
    Block() {}
    
    Block(uint8_t numRow, uint8_t numCol) {
      x = numRow * 8; 
      y = numCol * 8;; 
    }
    
    void show() {
      u8g.setHiColor(255);
      u8g.drawBox(x, y, width, width);
      u8g.setHiColor(0);
      u8g.drawFrame(x+1,y+1,width-2, width-2);
    }

    void update() {
      if (!hasReached()) {
        y = y + accel;
      }
    }

    bool hasReached() {
      uint8_t edgeY = y+width;
      return edgeY==64;
    }

    uint8_t x; uint8_t y; 

  private: uint8_t accel = 1;;
    uint8_t width = 7; 
}; 

const uint8_t numCols = 16; 
const uint8_t numRows = 8;

uint8_t numBlock = 0;
Block * blocks[numRows*numCols] = { NULL };
Block * block = NULL;
uint8_t blocksPerCol[numCols] = { 0 };

void setup(void) {
  Serial.begin(9600);
  u8g.begin();
  
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(0, nodeAddress);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  createBlock();
}

void createBlock() {
  uint8_t col = random(numCols); 
  while(blocksPerCol[col] == numRows) {
    Serial.print("Column full.");
    col = random(numCols); 
  }
  
  block = new Block(col, 0);
  blocks[numBlock] = block; 
  numBlock++;
}

void draw() { 
  for (int i = 0; i < numRows * numCols; i++) {
    if (blocks[i] != NULL) {
      blocks[i]->show();
    }
  }
}

void loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );

  // Check if block is intersecting with another block. 
  if (isIntersecting()) {
    createBlock();
  } else if (block->hasReached()) {
    createBlock();
  } else {
    block->update();
  }
}

boolean isIntersecting() {
  for (uint8_t j = 0; j < 128; j++) {
    if (blocks[j] != NULL) {
     if ((block->y+7 == blocks[j]->y - 1) && (block->x == blocks[j]->x)) {
        return true; 
     }
    }
  }

  return false;
}
