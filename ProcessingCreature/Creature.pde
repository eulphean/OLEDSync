class Creature {
  int xPos; int yPos; int curScreen; int prevScreen; 
  
  Creature() {
    xPos = 0; yPos = 0; curScreen = 0; prevScreen = 0;
  }
  
  void show() {
    fill(0);
    //ellipse(xPos * w, yPos * w, 16, 16);  
    rect(xPos * cellWidth, yPos * cellWidth, cellWidth, cellWidth);
  }
  
  void move(int x, int y) {
    int newXPos, newYPos; 
    if (x != 0) {
       // Move left or right
       if (x > 0) {
           newXPos = xPos + 1; 
          // Detect collision
          if (newXPos <= numCols -1) xPos++;
          // Else, ignore this move. 
       } else {
          // Detect collision
           newXPos = xPos - 1;
          if (newXPos >= 0) xPos--;
          // Else, ignore this move. 
       }
    }
    
    if (y != 0) {
       if (y > 0) {
         newYPos = yPos + 1; 
         if (newYPos <= numRows -1) yPos++; 
         // Else, ignore move
       } else {
         newYPos = yPos - 1; 
         if (newYPos >= 0) yPos--; 
         // Else, ignore this move. 
       }
    }
    
    // Move is done, find what screen did this creature land on. 
    curScreen = getScreenNum(xPos, yPos);
  }
  
  // Screen style
  //0 1
  //2 3
  //4 5
  //6 7
  //8 9
  // Return the board the creature is on for its xPos and yPos
  int getScreenNum(int xPos, int yPos) {
    int currentScreen = -1;
    if (xPos >= 0 && xPos <=7) {
      // Screen 0
       if (yPos >=0 && yPos <=15) currentScreen = 0; 
       
       // Screen 2
       if (yPos >=16 && yPos <=31) currentScreen = 2; 
       
       // Screen 4
       if (yPos >=32 && yPos <=47) currentScreen = 4; 
       
       // Screen 6
       if (yPos >=48 && yPos <= 63) currentScreen = 6; 
       
       // Screen 8
       if (yPos >=64 && yPos <=79) currentScreen = 8; 
    }
    
    if (xPos >= 8 && xPos <= 15) {
      // Screen 1
       if (yPos >=0 && yPos <=15) currentScreen = 1; 
       
       // Screen 3
       if (yPos >=16 && yPos <=31) currentScreen = 3; 
       
       // Screen 5
       if (yPos >=32 && yPos <=47) currentScreen = 5; 
       
       // Screen 7
       if (yPos >=48 && yPos <= 63) currentScreen = 7; 
       
       // Screen 9
       if (yPos >=64 && yPos <=79) currentScreen = 9; 
    }
    
    if (currentScreen == -1) {
      println("-------It should never come here. There is error--------");
    }
    
    return currentScreen; 
  }
};