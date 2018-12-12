// I'm making a quick prototype to test if I can move a creature around on the 
// OLEDs if I want to or not. These OLEDs are installed on the structure currently
// in a certain way. 

import processing.serial.*; 

int boardWidth = 128; // 64 * 2 // 2 Columns (128)
int boardHeight = 64; // 128 * 5 // 5 rows (640)
int w = 8; 

// Number of columns, number of rows. 
int numCols = boardWidth/w; int numRows = boardHeight/8; 

int [][] board = new int[numCols][numRows]; 
Serial myPort; 

Creature c = new Creature(); 

void setup() {
  size(130, 68);
  int len = Serial.list().length;
  printArray(Serial.list());
  println(Serial.list()[12]);
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[12], 9600);
}

void draw() {
  background(255);
  
  // Draw the board. 
  for (int y = 0; y < numRows; y++) {
    for (int x = 0; x < numCols; x++) {
        noFill();
        rect(x*w, y*w, w, w);
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
     
     println("Position: " + c.xPos + ',' + c.yPos);
     String a = c.xPos + "," + c.yPos + "."; 
     myPort.write(a);
  }
}

void serialEvent(Serial p) {
  // get message till line break (ASCII > 13)
  String message = myPort.readStringUntil(13);
  if (message != null) {
    println(message);
  }
}