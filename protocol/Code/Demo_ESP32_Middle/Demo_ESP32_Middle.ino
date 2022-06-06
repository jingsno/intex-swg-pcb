
// Define all I/O pins
#define FROM_DISP 17
#define TO_DISP 16
#define FROM_MAIN 18
#define TO_MAIN 19
#define RELAY 0

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
  Serial.println(F(""));
  Serial.println(F("Mainboard -> Display board: r=rise f=falling"));
  Serial.println(F("Display -> Main board: R=rise F=falling"));
  Serial.println(F("NOTE: ONLY SHOWS EDGE TRANSITIONS, NO DECODE! "));

  digitalWrite(TO_DISP, HIGH); // sets the TO_DISP signal to HIGH
  digitalWrite(TO_MAIN, HIGH); // sets the TO_MAIN signal to HIGH
}

void loop() {
  Serial.println(F(""));
  delay(1000);
}

void PinChangeISR0(){                                     // Pin FROM_MAIN (Interrupt 0) service routine
  if (digitalRead(FROM_MAIN) == LOW) {
    // Falling edge
    digitalWrite(TO_DISP,LOW);
    Serial.print(F("f"));
  }
 
  else {
    // Rising edge
    digitalWrite(TO_DISP,HIGH);
    Serial.print(F("r"));
  }
}


void PinChangeISR1(){                                     // Pin FROM_DISP (Interrupt 1) service routine
  if (digitalRead(FROM_DISP) == LOW) {
    // Falling edge
    digitalWrite(TO_MAIN,LOW);
    Serial.print(F("F"));
  }
  else {
    // Rising edge
    digitalWrite(TO_MAIN,HIGH);
    Serial.print(F("R"));
  }
}
