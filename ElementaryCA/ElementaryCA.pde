int [] cells = {1,0,1,0,0,0,0,1,0,1,1,1,0,0,0,1,1,1,0,0};
int [] newcells = new int[cells.length]; 
int [] ruleset = {0, 1, 0, 1, 1, 0, 1, 0};

void setup() {
  size(300, 300);
}

void draw() {
  for (int i = 0; i < cells.length; i++) {
     if (cells[i]==0) fill(255); 
     else fill(0); 
     stroke(0); 
     rect(i*10, 0, 10, 10);
  }
  
  // Updates the generation of the cells. 
  update(); 
  
  delay(500);
}

void update() {
   // Set first and last value of the new array
   newcells[0] = cells[0]; 
   newcells[newcells.length-1] = cells[cells.length - 1]; 
  
   for (int i = 1; i < cells.length-1; i++) {
     int left = cells[i-1]; 
     int middle = cells[i]; 
     int right = cells[i+1];
     
     newcells[i] = rules(left, middle, right); 
   }
   
   // Discard old cells for new cells created with new rules. 
   cells = newcells; 
}

int rules(int left, int middle, int right) {
  String s = "" + left + middle + right; 
  int index = Integer.parseInt(s, 2); 
  return ruleset[index]; 
}