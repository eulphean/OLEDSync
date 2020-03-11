/*
 *  Simple example to print Morse code on an OLED screen. 
 */

// Serial variables. 
String inputText = ""; // Holds the text from Serial
int inputTextLength = 0; // Length of the text

void setup()
{
  // Initialize Serial. 
  Serial.begin(9600);
  Serial.println("Begin");
}

void loop()
{
  // As soon as were write something in the serial port and press enter,
  // Serial.available() > 0. Serial.read() reads off 1 byte from the 
  // Serial buffer. 
  while (Serial.available()) {
    char inChar = Serial.read(); 
    if (inChar == '\n') {
      // Stick an end of string character at the end. 
      char buf[inputTextLength+1];
      inputText.toCharArray(buf, inputTextLength+1);
      int i = 0;
      while (buf[i]!='\0') {
        Serial.print(buf[i]); 
        i++;
      }
    } else {
      inputText += inChar; 
      inputTextLength++;
    }
  }

  delay(1000);
  
  // Reset input text and length. 
  inputText = "";
  inputTextLength = 0;
}

