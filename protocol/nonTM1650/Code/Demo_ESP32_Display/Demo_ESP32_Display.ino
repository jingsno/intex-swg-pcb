// Define all I/O pins
#define FROM_DISP 17
#define TO_DISP 16
#define FROM_MAIN 18
#define TO_MAIN 19
#define RELAY 0

void setup() {
  // put your setup code here, to run once:
  pinMode(FROM_MAIN,INPUT); // Receive data from main board
  pinMode(TO_DISP,OUTPUT);  // Send data to display board
  pinMode(FROM_DISP,INPUT); // Receive data from display board
  pinMode(TO_MAIN,OUTPUT); // Send data to main board

  digitalWrite(TO_DISP, HIGH); // sets the TO_DISP signal to HIGH
  digitalWrite(TO_MAIN, HIGH); // sets the TO_MAIN signal to HIGH
  Serial.begin(115200);
}

void loop() {
  word value;

  // All segments & LEDs are lit
  value = 0b11111111111111111111111111111111;
  write2display(value);
  delay(1000); // waits for a second

  // Left LEDs on, right 7-segment on
  value = 0b00000000111111111111111110011100;
  write2display(value);
  delay(1000); // waits for a second

  // Right LEDs on, left 7-segment On
  value = 0b11111111000000000110001111111111;
  write2display(value);
  delay(1000); // waits for a second

  // All LEDs off, 7-segment shows "00"
  value = 0b00111111001111110110001110011100;
  write2display(value);
  delay(1000); // waits for a second
}

void write2display(word value) {

  // Start with a low start pulse
  digitalWrite(TO_DISP, LOW);  
  delayMicroseconds(200);   
  
  // Loops through the 32-bit value, from left to right
  for(int i = 0, mask = 0x80000000; i < 32; i++, mask = (word)mask >> 1)
  {
      if (value & mask) 
      {
          // Bit is one/on - long pulse
          digitalWrite(TO_DISP, HIGH);  
          delayMicroseconds(800);           
      }
      else
      {
          // Bit is zero/off - short pulse
          digitalWrite(TO_DISP, HIGH);  
          delayMicroseconds(200);           
      }
      
      // Send spacer in-between
      digitalWrite(TO_DISP, LOW); 
      delayMicroseconds(200);
    }
    
  // Ends with signal returning to high
  digitalWrite(TO_DISP, HIGH); 
}
