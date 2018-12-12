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
     
     println("Current screen is: " + c.curScreen);
     
     int newPos[] = getPositionForScreens();
     String toTransmit = c.curScreen + "," + newPos[0] + "," + newPos[1]; 
     // Before screen change logic, send the screen number
     if (c.curScreen != c.prevScreen) {
       // Send the prev screen as well.
       toTransmit += "," + c.prevScreen + "."; 
  
       // Next time we send a blank for the prev screen so we don't use it. 
       c.prevScreen = c.curScreen; 
     } else {
       // Some arbitrary large number
       toTransmit += "," + 100 + "."; // End the transmission string.  
     }
     
     println(toTransmit);
     myPort.write(toTransmit);
  }
}

int [] getPositionForScreens() {
  int [] newPos = new int[2];
  switch (c.curScreen) {
     case 0: {
       newPos[0] = c.xPos; newPos[1] = c.yPos; 
       break;
     }
     
    case 1: {
     newPos[0] = c.xPos - 8; newPos[1] = c.yPos; 
     break;
   }
     
    case 2: {
     newPos[0] = c.xPos; newPos[1] = c.yPos - 16; 
     break;
   }
   
    case 3: {
     newPos[0] = c.xPos - 8; newPos[1] = c.yPos - 16; 
     break;
   }
   
   case 4: {
     newPos[0] = c.xPos; newPos[1] = c.yPos - 32; 
     break;
   }
   
   case 5: {
     newPos[0] = c.xPos - 8; newPos[1] = c.yPos - 32; 
     break;
   }
   
   case 6: {
     newPos[0] = c.xPos; newPos[1] = c.yPos - 48; 
     break;
   }
   
    case 7: {
     newPos[0] = c.xPos - 8; newPos[1] = c.yPos - 48; 
     break;
   }
    
   case 8: {
     newPos[0] = c.xPos; newPos[1] = c.yPos - 64; 
     break;
   }
   
   case 9: {
     newPos[0] = c.xPos - 8; newPos[1] = c.yPos - 64; 
     break;
   }
  
   default: {
     break;
   }
  }
  return newPos; 
}

void serialEvent(Serial p) {
  // get message till line break (ASCII > 13)
  String message = myPort.readStringUntil(13);
  if (message != null) {
    println(message);
  }
}