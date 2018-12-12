// I'm making a quick prototype to test if I can move a creature around on the 
// OLEDs if I want to or not. These OLEDs are installed on the structure currently
// in a certain way. 

import processing.serial.*; 

int boardWidth = 128; // 64 * 2 // 2 Columns (128)
int boardHeight = 640; // 128 * 5 // 5 rows (640)
int cellWidth = 8; 

// Total columns and total rows on the board. 
int numCols = boardWidth/cellWidth; int numRows = boardHeight/cellWidth; 

// Screens
int numScreenCols = 2; int numScreenRows = 5; 
int screenWidth = 64; int screenHeight = 128; // Dimension of each screen. 

// Total board area
int [][] board = new int[numCols][numRows]; 

Creature c = new Creature(); 

// Serial
Serial myPort; 
void setup() {
  size(130, 650);
  
  // Print an array of all the cells. 
  printArray(Serial.list());
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[11], 9600);
}

void draw() {
  background(255);
  
  // Red outline for the screens
  for (int x = 0; x < numScreenCols; x++) {
     for (int y = 0; y < numScreenRows; y++) {
        int a = 255 / (x+y+1);
        color c = color(a, a*2, a*3); // Red outline
        fill(c);
        rect(x*screenWidth, y*screenHeight, screenWidth, screenHeight);
     }
  }
  
  // Draw the board. 
  for (int y = 0; y < numRows; y++) {
    for (int x = 0; x < numCols; x++) {
        noFill();
        rect(x*cellWidth, y*cellWidth, cellWidth, cellWidth);
    }
  }

  // Show creature
  c.show();
}

void keyPressed() {
  if (key == CODED) {
     if (keyCode == RIGHT) {
        c.move(1, 0);
     }
     
     if (keyCode == LEFT) {
        c.move(-1, 0);
     }
     
     if (keyCode == UP) {
        c.move(0, -1);  
     }
     
     if (keyCode == DOWN) {
        c.move(0, 1);
     }
     
     int curScreen = getScreenNum(c.xPos, c.yPos);
     
     // Send current position to the uController. 
     String a = c.xPos + "," + c.yPos + "."; 
     myPort.write(a);
     
     // 
  }
}

// Screen style
//1 2
//3 4
//5 6
//7 8
//9 10
// Return the board the creature is on for its xPos and yPos
int getScreenNum(int xPos, int yPos) {
  int currentScreen = -1;
  if (xPos >= 0 && xPos <=7) {
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
  
  if (xPos >= 8 && xPos <= 15) {
    // Screen 1
     if (yPos >=0 && yPos <=15) currentScreen = 2; 
     
     // Screen 3
     if (yPos >=16 && yPos <=31) currentScreen = 4; 
     
     // Screen 5
     if (yPos >=32 && yPos <=47) currentScreen = 6; 
     
     // Screen 7
     if (yPos >=48 && yPos <= 63) currentScreen = 8; 
     
     // Screen 9
     if (yPos >=64 && yPos <=79) currentScreen = 10; 
  }
  
  
  
  if (currentScreen == -1) {
    println("-------It should never come here. There is error--------");
  } else {
    println("Current Screen: " + currentScreen); 
  }
  return currentScreen; 
}

void serialEvent(Serial p) {
  // get message till line break (ASCII > 13)
  String message = myPort.readStringUntil(13);
  if (message != null) {
    println(message);
  }
}