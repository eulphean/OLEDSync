int w = 8; int screenW = 128; int screenH = 640; 
int rows = screenH/w; int columns = screenW/w;
int [][] current = new int[columns][rows];
int [][] next = new int[columns][rows];

void setup() {
  size(128, 640);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
       current[j][i] = (int) random(2);
    }
  } 
}

void draw() {
  for ( int i = 0; i < rows; i++) {
    for ( int j = 0; j < columns; j++) {
      // Black when state = 1
      if ((current[j][i] == 1)) fill(0);
      // White when state = 0
      else fill(255);
      stroke(0);
      rect(j*w, i*w, w, w);
    }
  }
  
  generate();
}

void generate() {
  //int [][] next = new int[columns][rows];
  // Take into account first and last rows. 
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < columns; x++) {
       next[x][y] = rules(x, y); 
    }
  }
  
  // Copy complete array not just the reference. 
  // ArrayCopy was just copying the references and 
  // it was fucking things up. 
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < columns; x++) {
      current[x][y] = next[x][y];
    }
  }
}

int rules(int x, int y) {
  int neighbors = 0; 
  // Top, middle and bottom row. 
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      neighbors += current[(x+j+columns)%columns][(y+i+rows)%rows];
    }
  }

  // Subtract the state of current cell. 
  neighbors -= current[x][y]; 
  
  //// If it is alive and has less than 2 live neighbors, it dies from loneliness.
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