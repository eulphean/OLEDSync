#include "Arduino.h"
#include "U8glib.h"

const uint8_t numRows = 8; 
const uint8_t numCols = 16; 
const uint8_t cellWidth = 7; 

class Life {
  public:
    void init(U8GLIB_SH1106_128X64 * u8g, uint8_t seed) {
      randomSeed(seed);
      
      // Set display variable.
      oled = u8g;
      
      // Initialize both the arrays
      for (uint8_t y = 0; y < numRows; y++) {
        for (uint8_t x = 0; x < numCols; x++) {
          current[x][y] = random(2);
          next[x][y] = random(2);
        }
      }
    }
    
    void draw() {
       for ( int y = 0; y < numRows; y++) {
          for ( int x = 0; x < numCols; x++) {
            // Black when state = 1
            if ((current[x][y] == 1)) {
                // Give 1 px gap between blocks. 
                uint8_t a = x * (cellWidth+1); uint8_t b = y * (cellWidth+1); 
                oled->setHiColor(1);
                oled->drawBox(a, b, cellWidth, cellWidth);
                oled->setHiColor(0);
                oled->drawFrame(a+1,b+1,cellWidth-2, cellWidth-2);
            }
          }
        }
    }
    
    void updateScreen() {
      // Calculate next state based on current state. 
      for (int y = 0; y < numRows; y++) {
        for (int x = 0; x < numCols; x++) {
           next[x][y] = updateState(x, y); 
        }
      }

      // Copy next state into current state
      for (int y = 0; y < numRows; y++) {
        for (int x = 0; x < numCols; x++) {
           current[x][y] = next[x][y];
        }
      }
    }

    boolean isDone() {
      // Check if the entire screen has gone dark. Init again
      for (int y = 0; y < numRows; y++) {
        for (int x = 0; x < numCols; x++) {
           if (current[x][y] == 1) return false; 
        }
      }

      // If the loop continues till here, it's dark then. 
      return true;
    }

  private: 
    // Core Game of Life algorithm. 
    uint8_t updateState (uint8_t x, uint8_t y) {
      uint8_t neighbors = 0; 
      // Top, middle and bottom row
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          // Incorporate cell wrapping.  
          neighbors += current[(x+j+numCols)%numCols][(y+i+numRows)%numRows];
        }
      }
    
      // Subtract the state of current cell. 
      neighbors -= current[x][y]; 
      
      // If it is alive and has less than 2 live neighbors, it dies from loneliness.
      if ((current[x][y] == 1) && (neighbors <  2)) {
        return 0;
      }
    
      //If it is alive and has more than 3 live neighbors, it dies from overpopulation.
      else if ((current[x][y] == 1) && (neighbors >  3)) {
        return 0;
      }
      
      // If it is dead and has exactly 3 live neighbors, it is born!
      else if ((current[x][y] == 0) && (neighbors == 3)) {
        return 1;
      }
      // In all other cases, its state remains the same.
      else {
        return current[x][y];
      }
    }

    U8GLIB_SH1106_128X64 *oled;
    // Data structures to hold the state variables
    uint8_t current[numCols][numRows];
    uint8_t next[numCols][numRows];
};

