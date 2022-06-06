
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


// Define Buttons (not used in this code)
#define LED_OZONE           0x400  // 0b00000000000000000000010000000000 - Position 10 from right when staring on 0
#define LED_SLEEP           0x1000 // 0b00000000000000000001000000000000 - Position 12 from right when staring on 0
#define LED_BOOST           0x8000 // 0b00000000000000001000000000000000 - Position 15 from right when staring on 0
#define LED_POWER           0x800  // 0b00000000000000000000100000000000 - Position 11 from right when staring on 0
#define LED_PUMP_LOW_FLOW   0x40   // 0b00000000000000000000000001000000 - Position 06 from right when staring on 0
#define LED_LOW_SALT        0x20   // 0b00000000000000000000000000100000 - Position 05 from right when staring on 0
#define LED_HIGH_SALT       0x2    // 0b00000000000000000000000000000010 - Position 01 from right when staring on 0
#define LED_SERVICE         0x1    // 0b00000000000000000000000000000001 - Position 00 from right when staring on 0

// Segment-bit: DP G F E D C B A
#define DISP_BLANK  0b00000000
#define DISP_0      0b00111111
#define DISP_1      0b00000110
#define DISP_2      0b01011011
#define DISP_3      0b01001111
#define DISP_4      0b01100110
#define DISP_5      0b01101101
#define DISP_6      0b01111101
#define DISP_7      0b00000111
#define DISP_8      0b01111111
#define DISP_9      0b01101111
#define DISP_DP     0b10000000
#define DISP_A      0b01110111
#define DISP_P      0b01110011
#define DISP_1_CLEAN_06P 0b11111101
#define DISP_1_CLEAN_10P 0b10111111
#define DISP_1_CLEAN_14P 0b11100110

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

int i_isr0;
int i_isr1;
word displaydata = 0x0;
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
  
}

void loop() {

}

void PinChangeISR0(){                                     // Pin FROM_MAIN (Interrupt 0) service routine
  unsigned long Time_isr0 = micros();                          // Get current time
  
  if (digitalRead(FROM_MAIN) == LOW) {
    // Falling edge
    digitalWrite(TO_DISP,LOW);

      Time_isr0 = micros() - fall_Time_isr0;                        // Subtract last falling edge to get pulse time.

        // Looking for Data
        if ((Time_isr0 > bit0_MIN) && (Time_isr0 < bit0_MAX)) {
          // 0 bit
          bitWrite(displaydata,i_isr0,0);
          i_isr0++;
          //for debugging
          //Serial.print("0");

          //for debugging. NOTE breaks code due to too mutch data to serial
          //Serial.print("Pulse Time: ");
          //Serial.println(Time_isr0);            
        }
        else if ((Time_isr0 > bit1_MIN) && (Time_isr0 < bit1_MAX)) {
          // 1 bit
          bitWrite(displaydata,i_isr0,1);
          i_isr0++;
          //for debugging
          //Serial.print("1");
          //for debugging. NOTE breaks code due to too mutch data to serial
          //Serial.print("Pulse Time: ");
          //Serial.println(Time_isr0);            
        }
        else {
          // Not a 0 or 1 bit so restart data build

          //for debugging
          //Serial.println();
          //Serial.print("?");
          //Serial.println();          
          //for debugging. NOTE breaks code due to too mutch data to serial
          //Serial.print("Pulse Time: ");
          //Serial.println(Time_isr0);   
          
          i_isr0=0;
          displaydata=0x0;
        }

        if (i_isr0 >= 32) {
            // I'll just do somehing quick and dirty, for demo purposes
            // We're still in the interupt code, so we also need to set a global variable, and notify the main code
            // that we've have display data
           
              word tmpdisplaydata;
              // Loops through the 32-bit value, from left to right, reverses the bit order
              for(int i = 0, mask = 0x80000000; i < 32; i++, mask = (word)mask >> 1)
              {
                  if (displaydata & mask) 
                  {
                    bitWrite(tmpdisplaydata,i,1);         
                  }
                  else
                  {
                    bitWrite(tmpdisplaydata,i,0);      
                  }
               }

               displaydata = tmpdisplaydata;
           
            //Serial print binary value with zero padding
            //SerialPrintZeroPad32bit((int)displaydata);
   
            unsigned int LEFT_DIGIT = (unsigned int)displaydata >> 24;
            //Serial.print(" L:");
            //SerialPrintZeroPad8bit(LEFT_DIGIT);
                       
            unsigned int RIGHT_DIGIT =(unsigned int)displaydata >> 16;
            RIGHT_DIGIT =(unsigned int)RIGHT_DIGIT << 8;
            RIGHT_DIGIT =(unsigned int)RIGHT_DIGIT >> 8;
            //Serial.print(" R:");
            //SerialPrintZeroPad8bit(RIGHT_DIGIT);

            Serial.print(" [");
            Serial.print(getDisplayDigitFromCode( LEFT_DIGIT & 0b01111111));
            if (displaydata & (1 << 31)) { Serial.print("."); } else { Serial.print(" "); }
            Serial.print(getDisplayDigitFromCode( RIGHT_DIGIT & 0b01111111));
            if (displaydata & (1 << 23)) { Serial.print("."); } else { Serial.print(" "); }
            Serial.print("]");
            
            Serial.print(" LED: ");
            if (displaydata & (1 << 11)) { Serial.print("POWER=ON  "); } else { Serial.print("POWER=OFF "); }
            if (displaydata & (1 << 12)) { Serial.print("SLEEP=ON  "); } else { Serial.print("SLEEP=OFF "); }
            if (displaydata & (1 <<  6)) { Serial.print("PUMP_LOW_FLOW=ON  "); } else { Serial.print("PUMP_LOW_FLOW=OFF "); }
            if (displaydata & (1 <<  5)) { Serial.print("LOW_SALT=ON  "); } else { Serial.print("LOW_SALT=OFF "); }
            if (displaydata & (1 <<  1)) { Serial.print("HIGH_SALT=ON  "); } else { Serial.print("HIGH_SALT=OFF "); }            
            if (displaydata & (1 << 15)) { Serial.print("BOOST=ON  "); } else { Serial.print("BOOST=OFF "); }
            if (displaydata & (1 <<  0)) { Serial.print("SERVICE=ON  "); } else { Serial.print("SERVICE=OFF "); }
            if (displaydata & (1 << 10)) { Serial.print("OZONE=ON  "); } else { Serial.print("OZONE=OFF "); }

            Serial.print(" ");
            Serial.println(displaydata,HEX);

        }

      //for debugging       
      //Serial.print(F("F"));
      fall_Time_isr0 = micros();                               // Store fall time

  }
  else {
    // Rising edge
    digitalWrite(TO_DISP,HIGH);
    rise_Time_isr0 = Time_isr0;                                   // Store rise time
   //for debugging
   //Serial.print(F("R"));
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

char getDisplayDigitFromCode(uint8_t code) {
    switch (code) {
        case DISP_BLANK:  return ' ';
        case DISP_0: return '0';
        case DISP_1: return '1';
        case DISP_2: return '2';
        case DISP_3: return '3';
        case DISP_4: return '4';
        case DISP_5: return '5';
        case DISP_6: return '6';
        case DISP_7: return '7';
        case DISP_8: return '8';
        case DISP_9: return '9';
        case DISP_DP: return '.';
        case DISP_1_CLEAN_06P: return '6';
        case DISP_1_CLEAN_10P: return '0';
        case DISP_1_CLEAN_14P: return '4';
        default: return 0;
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
