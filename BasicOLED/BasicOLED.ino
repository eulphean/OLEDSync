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

    void setColsRows(uint8_t numCols, uint8_t numRows) {
      x = numCols * 8; y = numRows * 8;
    }
    
    void show() {
      u8g.setHiColor(1);
      u8g.drawBox(x, y, width, width);
      u8g.setHiColor(0);
      u8g.drawFrame(x+1,y+1,width-2, width-2);
    }

    void updateBlock() {
      if (!hasReachedBottom()) {
        y = y + accel;
      }
    }

    bool hasReachedBottom() {
      uint8_t edgeY = y+width;
      return edgeY==64;
    }

    ~Block() {}

    uint8_t x; uint8_t y; 

  private: uint8_t accel = 1;
    uint8_t width = 7; 
}; 

const uint8_t numCols = 16; 
const uint8_t numRows = 8;

uint8_t numBlocks = 0;
Block * blocks[numRows*numCols] = { NULL };
Block * currentBlock = NULL;
uint8_t blocksPerCol[numCols] = { 0 };

void setup(void) {
  Serial.begin(9600);
  u8g.begin();
  
  radio.begin();
  radio.enableDynamicPayloads();
  radio.openReadingPipe(0, nodeAddress);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  // Allocate memory for all the blocks.  
  for (int i = 0; i < 128; i++) {
    blocks[i] = new Block; 
  }

  // Assign the first block
  assignBlock();
}

void assignBlock() {
  // What happens when we have created all the blocks we wanted. 
  // We want to reset the screen.
  if (numBlocks < numRows*numCols) {
    uint8_t col = random(numCols); 
    while(blocksPerCol[col] == numRows) {
      col = random(numCols); 
    }

    // Increment blocks per column. 
    blocksPerCol[col]++;

    blocks[numBlocks]->setColsRows(col, 0);
    currentBlock = blocks[numBlocks]; 

    // Assign next block. 
    numBlocks++;
    
  } else {
    delay(1000);
    clearOLED(); 
    numBlocks = 0; 
    blocksPerCol[numCols] = { 0 };
    
    // Assign block
    assignBlock();
  }
}

void draw() { 
  for (int i = 0; i < numBlocks; i++) {
    blocks[i]->show();
  }
}

void loop(void) {
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );

  if (currentBlock != NULL) {
    Serial.println("Not null");
    if (shouldAssignNewBlock()) {
      assignBlock();
    } else {
      currentBlock->updateBlock();
    }
  }
}

boolean shouldAssignNewBlock() {
  // Has the block touched another block?
  for (int i = 0; i < numBlocks; i++) {
     if ((currentBlock->y + 7 == blocks[i]->y - 1) && (currentBlock->x == blocks[i]->x)) {
        return true; 
     }
  }

  // Has the block reached the bottom?
  if (currentBlock->hasReachedBottom()) {
    return true;
  }

  return false;
}

void clearOLED(){
    u8g.firstPage();  
    do {
    } while( u8g.nextPage() );
}

