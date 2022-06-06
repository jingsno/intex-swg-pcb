
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

// Constants
const unsigned long bit1_MIN = 800;
const unsigned long bit1_MAX = 1200;
const unsigned long bit0_MIN = 200;
const unsigned long bit0_MAX = 600;

// Interrupt variables
unsigned long fall_Time_isr0 = 0;       // Placeholder for microsecond time when last falling edge occured.
unsigned long rise_Time_isr0 = 0;       // Placeholder for microsecond time when last rising edge occured.
unsigned long fall_Time_isr1 = 0;       // Placeholder for microsecond time when last falling edge occured.
unsigned long rise_Time_isr1 = 0;       // Placeholder for microsecond time when last rising edge occured.

int i_isr1;
word inputbutton = 0x0;

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

}

void PinChangeISR0(){                                     // Pin FROM_MAIN (Interrupt 0) service routine
  if (digitalRead(FROM_MAIN) == LOW) {
    // Falling edge
    digitalWrite(TO_DISP,LOW);
    //for debugging
    //Serial.print("f");
  }
 
  else {
    // Rising edge
    digitalWrite(TO_DISP,HIGH);                             // Transmit to display
    //for debugging
    //Serial.print("r");
  }
}


void PinChangeISR1(){                                     // Pin FROM_DISP (Interrupt 1) service routine
  unsigned long Time_isr1 = micros();                          // Get current time
  
  if (digitalRead(FROM_DISP) == LOW) {
    // Falling edge
    digitalWrite(TO_MAIN,LOW);

      Time_isr1 = micros() - fall_Time_isr1;                        // Subtract last falling edge to get pulse time.

        // Looking for Data
        if ((Time_isr1 > bit0_MIN) && (Time_isr1 < bit0_MAX)) {
          // 0 bit
          bitWrite(inputbutton,i_isr1,0);
          i_isr1++;
          //for debugging
          //Serial.print("0");
          //for debugging. NOTE breaks code due to too mutch data to serial
          //Serial.print("Pulse Time: ");
          //Serial.println(Time);            
        }
        else if ((Time_isr1 > bit1_MIN) && (Time_isr1 < bit1_MAX)) {
          // 1 bit
          bitWrite(inputbutton,i_isr1,1);
          i_isr1++;
          //for debugging
          //Serial.print("1");
          //for debugging. NOTE breaks code due to too mutch data to serial
          //Serial.print("Pulse Time: ");
          //Serial.println(Time);            
        }
        else {
          // Not a 0 or 1 bit so restart data build

          //for debugging
          //Serial.println();
          //Serial.print("?");
          //Serial.println();          
          //for debugging. NOTE breaks code due to too mutch data to serial
          //Serial.print("Pulse Time: ");
          //Serial.println(Time);   
          
          i_isr1=0;
          inputbutton=0x0;
        }

        if (i_isr1 >= 16) {
            // Ok! Here we really need to reverse the bit order of the inputbutton variable, strip away the first byte, 
            // and we are left with the button values in the declarations. 
            // But I've spendt to much time on this, so I'll just do somehing quick and dirty, for demo purposes
            // We're still in the interupt code, so we also need to set a global variable, and notify the main code
            // that we've have a button press

              word tmpinputbutton;
              // Loops through the 16-bit value, from left to right, reverses the bit order
              for(int i = 0, mask = 0x8000; i < 16; i++, mask = (word)mask >> 1)
              {
                  if (inputbutton & mask) 
                  {
                    bitWrite(tmpinputbutton,i,1);         
                  }
                  else
                  {
                    bitWrite(tmpinputbutton,i,0);      
                  }
               }

            inputbutton = tmpinputbutton;
           
            //Serial print binary value with zero padding
            //SerialPrintZeroPad8bit((int)inputbutton & 0b11111111);
            //Serial.print(" "); 
           
            switch ((int)inputbutton & 0b11111111) {
              case BUTTON_LOCK: // Lock
                Serial.println("[Lock]");
                break;
              case BUTTON_TIMER: // Timer
                Serial.println("[Timer]");
                break;
              case BUTTON_POWER: // Power
                Serial.println("[Power]");
                break;
              case BUTTON_SELF_CLEAN: // Self-Clean
                Serial.println("[Self-Clean]");
                break;
              case BUTTON_BOOST: // Boost
                Serial.println("[Boost]");
                break;               
              case BUTTON_RELEASE: // Button Releaset
                Serial.println("[Button Release]");               
                break;
              default:
                break;
            }
}

      //for debugging       
      //Serial.print(F("F"));
      fall_Time_isr1 = micros();                               // Store fall time

  }
  else {
    // Rising edge
    digitalWrite(TO_MAIN,HIGH);
    rise_Time_isr1 = Time_isr1;                                   // Store rise time
   //for debugging
   //Serial.print(F("R"));
  }
}

void SerialPrintZeroPad32bit(int var) {
  for (unsigned int test = 0x80000000; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
  //Serial.println();
}

void SerialPrintZeroPad16bit(int var) {
  for (unsigned int test = 0x8000; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
  //Serial.println();
}


void SerialPrintZeroPad8bit(int var) {
  for (unsigned int test = 0x80; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
  //Serial.println();
}
