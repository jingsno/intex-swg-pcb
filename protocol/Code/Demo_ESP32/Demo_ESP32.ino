// Define all I/O pins
#define FROM_DISP 17
#define TO_DISP 16
#define FROM_MAIN 18
#define TO_MAIN 19
#define RELAY 2

// Define Buttons
#define DEBOUNCE              50 // 50mS delay before releasing buttons
#define BUTTON_BOOST        0x10 // 0b11101111 00010000 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_TIMER        0x02 // 0b11111101 00000010 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_POWER        0x04 // 0b11111011 00000100 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_LOCK         0x01 // 0b11111110 00000001 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_SELF_CLEAN   0x08 // 0b11110111 00001000 (The first 8 inverted bits are generated in the subroutine)
#define BUTTON_RELEASE      0x00 // 0b11111111 00000000 (The first 8 inverted bits are generated in the subroutine)

// Define LEDs
#define LED_OZONE           0x400  // 0b00000000 00000000 00000100 00000000
#define LED_SLEEP           0x1000 // 0b00000000 00000000 00010000 00000000
#define LED_BOOST           0x8000 // 0b00000000 00000000 10000000 00000000
#define LED_POWER           0x800  // 0b00000000 00000000 00001000 00000000
#define LED_PUMP_LOW_FLOW   0x40   // 0b00000000 00000000 00000000 01000000
#define LED_LOW_SALT        0x20   // 0b00000000 00000000 00000000 00100000
#define LED_HIGH_SALT       0x2    // 0b00000000 00000000 00000000 00000010
#define LED_SERVICE         0x1    // 0b00000000 00000000 00000000 00000001

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
#define DISP_1_CLEAN_06P 0b11111101 // Right Disp, My SWG does not show "." in right display when in clean mode
#define DISP_1_CLEAN_10P 0b10111111 // Right Disp, My SWG does not show "." in right display when in clean mode
#define DISP_1_CLEAN_14P 0b11100110 // Right Disp, My SWG does not show "." in right display when in clean mode

// Define pulse lengts
const unsigned long bit1_MIN = 800;
const unsigned long bit1_MAX = 1200;
const unsigned long bit0_MIN = 200;
const unsigned long bit0_MAX = 600;

// Interrupt variables
unsigned long fall_Time_isr0 = 0;       // isr0 placeholder for microsecond time when last falling edge occured.
unsigned long rise_Time_isr0 = 0;       // isr0 placeholder for microsecond time when last rising edge occured.

unsigned long fall_Time_isr1 = 0;       // isr1 placeholder for microsecond time when last falling edge occured.
unsigned long rise_Time_isr1 = 0;       // isr1 placeholder for microsecond time when last rising edge occured.

int relay_state = LOW;  // the current state of relay

int i_isr0;
int i_isr1;

word tmpdisplaydata;
word tmpinputbutton;
word displaydata = 0x0;
word inputbutton = 0x0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println(F("SETUP: MAIN_BOARD -> ESP32 -> DISPLAY_BOARD"));
  pinMode(FROM_MAIN,INPUT); // Receive data from main board
  Serial.println(F("FROM_MAIN (Pin 18) Configured for input from main board."));
  attachInterrupt(FROM_MAIN,PinChangeISR0,CHANGE);
  Serial.println(F("FROM_MAIN (Pin 18) ISR0 function attached."));

  pinMode(TO_DISP,OUTPUT);  // Send data to display board
  digitalWrite(TO_DISP, HIGH); // sets the TO_DISP signal to HIGH
  Serial.println(F("TO_DISP   (Pin 16) Configured for output to display board."));

  Serial.println();

  Serial.println(F("SETUP: DISPLAY_BOARD -> ESP32 -> MAIN_BOARD"));
  pinMode(FROM_DISP,INPUT); // Receive data from display board
  Serial.println(F("FROM_DISP (Pin 17) Configured for input from display board."));
  attachInterrupt(17,PinChangeISR1,CHANGE);
  Serial.println(F("FROM_DISP (Pin 17) ISR1 function attached."));
 
  pinMode(TO_MAIN,OUTPUT); // Send data to main board
  digitalWrite(TO_MAIN, HIGH); // sets the TO_MAIN signal to HIGH
  Serial.println(F("TO_MAIN   (Pin 19) Configured for output to main board."));

  Serial.println();

  Serial.println(F("[Self-Clean]+[Boost] will toggle relay"));

  // Configures relay, and sets it to low/off
  pinMode(RELAY, OUTPUT); 
  digitalWrite(RELAY, LOW);
  
}

void loop() {

// We do nothing here!

}

// Interupt routine; read data from mainboard. Triggers on "FROM_MAIN" pin change
void PinChangeISR0(){                                     // Pin FROM_MAIN (Interrupt 0) service routine
  unsigned long Time_isr0 = micros();                     // Get current time
  
  if (digitalRead(FROM_MAIN) == LOW) {
    // Falling edge
    digitalWrite(TO_DISP,LOW);

      Time_isr0 = micros() - fall_Time_isr0;              // Subtract last falling edge to get pulse time.

        // Looking for Data
        if ((Time_isr0 > bit0_MIN) && (Time_isr0 < bit0_MAX)) {
          // 0 bit
          bitWrite(displaydata,i_isr0,0);
          i_isr0++;
        }
        else if ((Time_isr0 > bit1_MIN) && (Time_isr0 < bit1_MAX)) {
          // 1 bit
          bitWrite(displaydata,i_isr0,1);
          i_isr0++;
        }
        else {
          // Not a 0 or 1 bit so restart data build
          i_isr0=0;
          displaydata=0x0;
        }

        // Do we have a complete bitstream?
        if (i_isr0 >= 32) {
            // We're still in the interupt code, so we also need to set a global variable, and notify the main code
            // that we've have display data
           
              tmpdisplaydata=0x0;
              
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
           
            // Get left digit   
            unsigned int LEFT_DIGIT = (unsigned int)displaydata >> 24;
                       
            // Get right digit
            unsigned int RIGHT_DIGIT =(unsigned int)displaydata >> 16;
            RIGHT_DIGIT =(unsigned int)RIGHT_DIGIT << 8;
            RIGHT_DIGIT =(unsigned int)RIGHT_DIGIT >> 8;

            // Print LED display
            Serial.print(" [");
            Serial.print(getDisplayDigitFromCode( LEFT_DIGIT & 0b01111111));  // Left 7-segment
            Serial.print(getDisplayDigitFromCode( LEFT_DIGIT & DISP_DP));     // Left .
            Serial.print(getDisplayDigitFromCode( RIGHT_DIGIT & 0b01111111)); // Right 7-segment
            Serial.print(getDisplayDigitFromCode( RIGHT_DIGIT & DISP_DP));    // Right .
            Serial.print("]");

            // Print Status LEDs
            Serial.print(" LED: ");
            if (displaydata & LED_POWER)        { Serial.print("POWER=ON  "); } else { Serial.print("POWER=OFF "); }
            if (displaydata & LED_SLEEP)        { Serial.print("SLEEP=ON  "); } else { Serial.print("SLEEP=OFF "); }
            if (displaydata & LED_PUMP_LOW_FLOW){ Serial.print("PUMP_LOW_FLOW=ON  "); } else { Serial.print("PUMP_LOW_FLOW=OFF "); }
            if (displaydata & LED_LOW_SALT)     { Serial.print("LOW_SALT=ON  "); } else { Serial.print("LOW_SALT=OFF "); }
            if (displaydata & LED_HIGH_SALT)    { Serial.print("HIGH_SALT=ON  "); } else { Serial.print("HIGH_SALT=OFF "); }            
            if (displaydata & LED_BOOST)        { Serial.print("BOOST=ON  "); } else { Serial.print("BOOST=OFF "); }
            if (displaydata & LED_SERVICE)      { Serial.print("SERVICE=ON  "); } else { Serial.print("SERVICE=OFF "); }
            if (displaydata & LED_OZONE)        { Serial.print("OZONE=ON  "); } else { Serial.print("OZONE=OFF "); }

            Serial.print(" ");
            Serial.println(displaydata,HEX);
        }

      fall_Time_isr0 = micros();                               // Store fall time

  }
  else {
    // Rising edge
    digitalWrite(TO_DISP,HIGH);
    rise_Time_isr0 = Time_isr0;                                   // Store rise time
  }
}


// Interupt routine; read data from display. Triggers on "FROM_DISP" pin change
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
        }
        else if ((Time_isr1 > bit1_MIN) && (Time_isr1 < bit1_MAX)) {
          // 1 bit
          bitWrite(inputbutton,i_isr1,1);
          i_isr1++;
        }
        else {
          // Not a 0 or 1 bit so restart data build
          i_isr1=0;
          inputbutton=0x0;
        }

        // Do we have a complete bitstream?
        if (i_isr1 >= 16) {

            // We're still in the interupt code, so we also need to set a global variable, and notify the main code
            // that we've have a button press

              tmpinputbutton=0x0;
              
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

            // Strip first 8 bits
            inputbutton = ((int)tmpinputbutton & 0b11111111);

            if (inputbutton & BUTTON_LOCK)       {Serial.print("[Lock]"); }
            if (inputbutton & BUTTON_TIMER)      {Serial.print("[Timer]"); }
            if (inputbutton & BUTTON_POWER)      {Serial.print("[Power]"); }
            if (inputbutton & BUTTON_SELF_CLEAN) {Serial.print("[Self-Clean]");}
            if (inputbutton & BUTTON_BOOST)      {Serial.print("[Boost]"); }
            if (inputbutton & (BUTTON_LOCK | BUTTON_TIMER | BUTTON_POWER | BUTTON_SELF_CLEAN | BUTTON_BOOST)) { Serial.println(); }

            if (inputbutton == BUTTON_RELEASE)    {Serial.println("[Button Release]"); }
            
            // Toggle relay ?
            if ((inputbutton & BUTTON_SELF_CLEAN) && (inputbutton & BUTTON_BOOST)) {Serial.println("[RELAY TOGGLE]");  relay_state = !relay_state;}
            digitalWrite(RELAY, relay_state);
}

      fall_Time_isr1 = micros();                               // Store fall time

  }
  else {
    // Rising edge
    digitalWrite(TO_MAIN,HIGH);
    rise_Time_isr1 = Time_isr1;                                   // Store rise time
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
}

void SerialPrintZeroPad16bit(int var) {
  for (unsigned int test = 0x8000; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
}


void SerialPrintZeroPad8bit(int var) {
  for (unsigned int test = 0x80; test; test >>= 1) {
    Serial.write(var  & test ? '1' : '0');
  }
}
