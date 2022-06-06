// Define all I/O pins
#define FROM_DISP 17
#define TO_DISP 16
#define FROM_MAIN 18
#define TO_MAIN 19
#define RELAY 0

// Define Buttons
#define DEBOUNCE              50 // 50mS delay before releasing buttons
#define BUTTON_BOOST        0x10 // 0b1110111100010000 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_TIMER        0x02 // 0b1111110100000010 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_POWER        0x04 // 0b1111101100000100 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_LOCK         0x01 // 0b1111111000000001 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_SELF_CLEAN   0x08 // 0b1111011100001000 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_RELEASE      0x00 // 0b1111111100000000 (The first 8 inverted bits are generated in the subroutine)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(FROM_MAIN,INPUT); // Receive data from main board
  Serial.println(F("FROM_MAIN (Pin 18) Configured for main board input."));
  attachInterrupt(FROM_MAIN,PinChangeISR0,CHANGE);
  Serial.println(F("FROM_MAIN (Pin 18) ISR0 function attached."));
  pinMode(TO_DISP,OUTPUT);  // Send data to display board
  Serial.println(F("TO_DISP (Pin 16) Configured for display board output."));
  
  pinMode(FROM_DISP,INPUT); // Receive data from display board
  Serial.println(F("FROM_DISP (Pin 17) Configured for display board input."));
  attachInterrupt(17,PinChangeISR1,CHANGE);
  Serial.println(F("FROM_DISP (Pin 17) ISR1 function attached."));
  pinMode(TO_MAIN,OUTPUT); // Send data to main board
  Serial.println(F("TO_MAIN (Pin 19) Configured for main board output."));

  digitalWrite(TO_DISP, HIGH); // sets the TO_DISP signal to HIGH
  digitalWrite(TO_MAIN, HIGH); // sets the TO_MAIN signal to HIGH

}

void loop() {
  word value;
  
  delay(5000); // Wait for 5 seconds

  // Push Center/Power button
  write2main(BUTTON_POWER);
 
  delay(2000); // Waits for two seconds

  // Push West/Lock button
  write2main(BUTTON_LOCK);
 
  delay(1000); // Wait for one second

  // Push East/Timer button 6-times
  int runXTimes = 0;
  for (; runXTimes < 6; runXTimes++) {

    write2main(BUTTON_TIMER);
    delay(500); // Wait for 0.5 seconds
  }

  delay(1500); // Waits for 0.5 + 1.5 seconds

  // Push West/Lock button
  write2main(BUTTON_LOCK);

  delay(2000); // Wait for 2 seconds

  // Push Center/Power button
  write2main(BUTTON_POWER);

  // Wait for 5 seconds
  delay(5000);
}

void write2main(word value) {

  // Start with a low start pulse
  digitalWrite(TO_MAIN, LOW);  
  delayMicroseconds(200);   

  // Generate the full 16b-bit transmitted sequence: First byte is inverted value, second is value passed to this subroutine
  word transmitvalue = ((value^0b11111111)<<8)+value;
 
  // Loops through the 16-bit value, from left to right
  for(int i = 0, mask = 0x8000; i < 16; i++, mask = (word)mask >> 1)
  {
      if (transmitvalue & mask) 
      {
          // Bit is one/on - long pulse
          digitalWrite(TO_MAIN, HIGH);  
          delayMicroseconds(800);           
      }
      else
      {
          // Bit is zero/off - short pulse
          digitalWrite(TO_MAIN, HIGH);  
          delayMicroseconds(200);           
      }
      
      // Send spacer in-between
      digitalWrite(TO_MAIN, LOW); 
      delayMicroseconds(200);
    }
    
  // Ends with signal returning to high
  digitalWrite(TO_MAIN, HIGH);

  // Debounce and transmit release button code, if not already in Release button loop. Coud have been written "if (transmitvalue != 0xFF00)"
  if (transmitvalue != ((BUTTON_RELEASE^0b11111111)<<8)+BUTTON_RELEASE) {
     delay(DEBOUNCE);
     write2main(BUTTON_RELEASE);
  }
}

void PinChangeISR0(){                                     // Pin FROM_MAIN (Interrupt 0) service routine
  if (digitalRead(FROM_MAIN) == LOW) {
    // Falling edge
    digitalWrite(TO_DISP,LOW);
    //Serial.print(F("f"));
  }
 
  else {
    // Rising edge
    digitalWrite(TO_DISP,HIGH);
    //Serial.print(F("r"));
  }
}


void PinChangeISR1(){                                     // Pin FROM_DISP (Interrupt 1) service routine
  if (digitalRead(FROM_DISP) == LOW) {
    // Falling edge
    digitalWrite(TO_MAIN,LOW);
    //Serial.print(F("F"));
  }
  else {
    // Rising edge
    digitalWrite(TO_MAIN,HIGH);
    //Serial.print(F("R"));
  }
}
