class Creature {
  public
    Creature() {
      xPos = 0; yPos = 0; 
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
    }
    
  private
    int xPos; int yPos;
};