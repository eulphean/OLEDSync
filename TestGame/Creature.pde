class Creature {
  public
    Creature() {
      xPos = 1; yPos = 1; 
    }
    
    void show() {
      fill(0);
      //ellipse(xPos * w, yPos * w, 16, 16);  
      rect(xPos * w, yPos * w, w, w);
    }
    
    void move(int x, int y) {
      if (x != 0) {
         // Move left or right
         if (x > 0) {
            // Detect collision
            xPos++;
         } else {
            // Detect collision
            xPos--; 
         }
      }
      
      if (y != 0) {
         if (y > 0) {
            // Detect collision
            yPos++; 
         } else {
            // Detect collision
            yPos--; 
         }
      }
    }
    
  private
    int xPos; int yPos;
};