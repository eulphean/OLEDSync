class Food {
  int xPos; int yPos; 
  int foodWidth = cellWidth; int foodHeight = foodWidth;
  
  Food() {
     // Assign food position within world dimensions. 
     xPos = (int) random(0, worldWidth - foodWidth); 
     yPos = (int) random(0, worldHeight - foodHeight);
  }
  
  void show() {
     fill(0);
     rect(xPos, yPos, foodWidth, foodHeight);
  }
}