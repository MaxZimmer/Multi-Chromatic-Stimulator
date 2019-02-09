/* ------------------------------------------------------------------------------------
 Multi Chromatic Stimulator can individually control up to 24 LEDs.
 The script relies on the incoming blanking signal which updates the LEDs.
 A trigger signal is generated at the bigining of each array possition.
 Library "Adafruit TLC5947" needs to be installed.
 The default script is parametered for 4 LEDs: R, G, B, UV.
 ------------------------------------------------------------------------------------*/

int           nLoops           = 500;   //  Number of repeats of the arrays (i.e. Loops)
const int     nArrayEntries    = 7;    //  Number of entries in the arrays, including preadaption at position 0
int           Scan_Logic       = 2;    //  Scanning logic (1 for 1ms scans, 2 for 2ms scans)


// // // // // // // // // // // // // // // // // // // // // // // // // // //
// // // // // // // // // STIMULUS SEQUENCE START // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // // // // // // 

const int8_t arrayR[] PROGMEM = {
0,100,100,100,100,100,100,100,0
};
const int8_t arrayG[] PROGMEM = {    
0,0,100,100,100,100,100,0,0
};
const int8_t arrayB[] PROGMEM = {    
0,0,0,100,100,100,0,0,0
};
const int8_t arrayU[] PROGMEM = {
0,0,0,0,100,0,0,0,0
};
const int16_t PulseArray[] PROGMEM = {      
5,5,5,5,5,5,5,5,5
};


// // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // //  STIMULUS SEQUENCE END  // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // //




/* ------------------------------------------------------------------------------------
   Internal Definitions (Change at your own risk)
*/

#include "Adafruit_TLC5947.h"
#include <SPI.h>
#include "LED_Values.h"

#define data   4    // SPI connection, DIN connected to pin D4
#define clock  5    // SPI connection, CLK connected to pin D5
#define latch  6    // SPI connection, LAT connected to pin D6
#define oe     2    // Optional feature to prevent LED to light up when powering up the TLC board

Adafruit_TLC5947 tlc = Adafruit_TLC5947(1, clock, data, latch);

int Red    =  0; // Red LED TLC pin
int Green  =  1; // Green LED TLC pin
int Blue   =  2; // Blue LED TLC pin
int UV     =  3; // UV LED TLC pin

//int aa = 1;

int LoopTime_s = 2;   //Loop duration in seconds

const  int    pSyncOut   = A0;  // Trigger channel must be connected to A0 pin on the Arduino
const  byte   pBlank     = 3;   // Blanking signal channel must be connected to digital pin 3 on the Arduino


volatile int stred= 100;
volatile int stgreen= 100;
volatile int stblue= 100;
volatile int stuv = 100;    // LED values
char       sCmd;                            // Serial monitor

int Trigger_Duration = 25;                  // Trigger duration in ms

volatile int   iLoop = 0;                   // Actual loop number = iLoop + 1
volatile word  PulseCount = 0;              // Count the number of pulses delivered by the blanking signal
volatile int   PulseCount_trigger = 0;      // Count the number of pulses generated for the trigger channel (A0 pin)
volatile int   ArrayPosition = 0;           // Position array within the current loop

float  x_Logic      =  2; //Scan_Logic/2.0;                   // Factor applied to the timing according to the scanning logic
float  Trigger_dur  =  Trigger_Duration; //* x_Logic;       // Trigger duration adjusted



/* -----------------------------------------------------------------------------------
        Internal methods
 ------------------------------------------------------------------------------------*/
 
void setup(){
  
// Initialize the serial communication with PC
  Serial.begin(9600);
  pinMode(pSyncOut, OUTPUT);  
  digitalWrite(pSyncOut, LOW); 
  pinMode(pBlank, INPUT_PULLUP);
  digitalWrite(pBlank, HIGH);
  tlc.begin();
  tlc.write();

//Prevent LEDs from lighting up initially
    if (oe >= 0) {
      pinMode(oe, OUTPUT);
      digitalWrite(oe, LOW);
    }
}

/* ----------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------*/

// LED function
void LED(int i, int pwm) {
  tlc.setPWM(i, pwm);
  tlc.write();
}

/* ----------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------*/

// Turn all LED off
void Play0(){
  LED(Red,0);      // Set Red LED to 0  
  LED(Green,0);    // Set Green LED to 0 
  LED(Blue,0);     // Set Blue LED to 0 
  LED(UV,0);       // Set UV LED to 0 
}

/* ----------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------*/




/* ----------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------*/

// Play stimulus function at LED "Natural stat values"
void  PlayArraysNat () { 
/* Feeding LED values according to the current position array *--------------------*/
    stred   =     pgm_read_byte_near(arrayR + ArrayPosition); // Set Red LED values
    stgreen =     pgm_read_byte_near(arrayG + ArrayPosition); // Set Green LED values
    stblue  =     pgm_read_byte_near(arrayB + ArrayPosition); // Set Blue LED values
    stuv    =     pgm_read_byte_near(arrayU + ArrayPosition); // Set UV LED values
    
    LED(Red,stred/100*maxRNat);         // update the Red LED value
    LED(Green,stgreen/100*maxGNat);     // update the Grenn LED value
    LED(Blue,stblue/100*maxBNat);       // update the Blue LED value
    LED(UV,stuv/100*maxUNat);           // update the UV LED value

   

  /* Trigger ------------------------------------------------------------------------*/
  if (PulseCount < Trigger_dur){      // Determine Trigger_pulse duration
    digitalWrite(pSyncOut,1);         // Set Trigeer output to 1
  }
  else {                              // Once Trigger duration reached
    digitalWrite(pSyncOut,0);         // Set Trigger output to 1
  }

  
  /* Moving Through the stimulus ----------------------------------------------------*/
 
  PulseCount += 1;      // Pulse Counter, move to the next pulse


  if(PulseCount == (pgm_read_word_near(PulseArray+ArrayPosition)/1000)){   // When the pulse counter reaches the current position array duration 
    ArrayPosition += 1;                                                       // Move to the next position array
    PulseCount = 0;                                                           // Reset the pulse counter
  } 

  if (iLoop == 0 && ArrayPosition == 1 && PulseCount ==0){
    Serial.println("Loop 1");
  }
  
  if(ArrayPosition == nArrayEntries){     // When current iLoop has reached the last ArrayPosition
    iLoop += 1;                           // Move to the next loop
    ArrayPosition = 1;                    // Reset the position array and skip the preadaptation (ArrayPosition = 0)
    if(iLoop<=nLoops-1){
      Serial.print("Loop ");
      Serial.println(iLoop+1);
    }
  }
   
  if(iLoop == nLoops){                                   // When Array has completed its last loop
    detachInterrupt(digitalPinToInterrupt(pBlank));      // Stop blanking signal  
    Play0();                                             // Turn off all LEDs
    PulseCount = 0;                                      // Reset Pulse Counter
    ArrayPosition = 0;                                   // Reset Array Counter   
    iLoop = 0;                                           // Reset Loop Counter 
    Serial.println(" ...Done");                          // End of stimulus print   
  }
}

/* ----------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------*/


// // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // //  Main loop // // // // // // // // // // //
// // // // // // // // // // // // // // // // // // // // // // // 
 
void loop() {
  
  // Check if command received from PC
  while(true){
    
    if(Serial.available()>0) {
      sCmd = Serial.read();

    // Execute command
      switch (sCmd) {

        case 'a':
          // Array Stimulus at "Full power"
          Serial.println("Playing Arrays, LED set at equal intensity (press '0' to abort)");  
          Serial.print(nLoops);
          Serial.println(" Loops");
          Serial.print(LoopTime_s);
          Serial.println(" Seconds per Loop");
          Serial.println("Preadapt...");
          attachInterrupt(digitalPinToInterrupt(pBlank), PlayArrays, FALLING);
          digitalWrite(pSyncOut,0); 
              
          break;

        case 'b':
          // Array Stimulus at "Nat Stat values"
          Serial.println("Playing Arrays, LED set at Natural Statistic intensity (press '0' to abort)");  
          Serial.print(nLoops);
          Serial.println(" Loops");
          Serial.print(LoopTime_s);
          Serial.println(" Seconds per Loop");
          attachInterrupt(digitalPinToInterrupt(pBlank), PlayArraysNat, FALLING);
          digitalWrite(pSyncOut,0); 
          Serial.println("Preadapt..."); 
          break;

          
        case '0':
          // All LEDs off
          detachInterrupt(digitalPinToInterrupt(pBlank));
          digitalWrite(pSyncOut,0);
          Play0();                // All LED to 0
          Serial.println("-> All LEDs off"); 
          PulseCount = 0;         // Reset pulse counter
          ArrayPosition = 0;      // Reset position array
          iLoop = 0;              // Reset loop counter                    
          break;

        case '1': 
          // Red LED to max power
          detachInterrupt(digitalPinToInterrupt(pBlank));  
          LED(Red,maxRNat);  
          Serial.println("-> Red LED to Nat full power");   
          Serial.println(LoopTime_s);                                                
          break;

        case '2':
          // Red LED at Nat stat max value
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Red,maxR);      
          Serial.println("-> Red LED to full power");                                        
          break;

        case '3':
          // Green LED at max power
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Green,maxGNat);      
          Serial.println("-> Green LED to Nat full power ");                                                                                      
          break;

        case '4':
          // Green LED at Nat stat max value
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Green,maxG); 
          Serial.println("-> Green LED to full power");                                                                        
          break;
          
        case '5':
          // Blue LED at max power
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Blue,maxBNat);      
          Serial.println("-> Blue LED to Nat full power");                                                                       
          break;

        case '6':
          // Blue LED at Nat stat max value
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Blue,maxB); 
          Serial.println("-> Blue LED to full power");                                                                                        
          break;
          
        case '7':
          // UV LED at max power
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(UV,maxUNat);      
          Serial.println("-> UV LED to Nat full power ");                                                                                       
          break;

        case '8':
          // UV LED at Nat stat max value
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(UV,maxU); 
          Serial.println("-> UV LED to full power");                                                                                     
          break;

        case '-':
          // All LEDs at max power
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Red,maxRNat); 
          LED(Green,maxGNat); 
          LED(Blue,maxBNat); 
          LED(UV,maxUNat); 
          Serial.println("-> Red LED to Nat full power");                                        
          Serial.println("-> Green LED to Nat full power");                                        
          Serial.println("-> Blue LED to Nat full power");                                        
          Serial.println("-> UV LED to Nat full power");                                                                                     
          break;

        case '+':
          // ALL LEDs at Nat stat max value
          detachInterrupt(digitalPinToInterrupt(pBlank));
          LED(Red,maxR); 
          LED(Green,maxG); 
          LED(Blue,maxB); 
          LED(UV,maxU); 
          Serial.println("-> Red LED to full power");                                        
          Serial.println("-> Green LED to full power");                                        
          Serial.println("-> Blue LED to full power");                                        
          Serial.println("-> UV LED to full power");                                                                        
          break;      

// ##################################################################################
          
        case '?' :
          Serial.println("Unknown command. ");
          Serial.println("The following commands are valid:");   
          Serial.println("- -> all LED to Natural Statistic max power");  
          Serial.println("+ -> all LED to maximum");      
          Serial.println("0 -> all LEDs off");                
          Serial.println("1 -> Red LED to Natural Statistic max power");                        
          Serial.println("2 -> Red LED to maximum");   
          Serial.println("3 -> Green LED to Natural Statistic max power");                        
          Serial.println("4 -> Green LED to maximum");                        
          Serial.println("5 -> Blue LED to Natural Statistic max power");                        
          Serial.println("6 -> Blue LED to maximum");           
          Serial.println("7 -> UV LED to Natural Statistic max power");                        
          Serial.println("8 -> UV LED to maximum");       
          Serial.println("a -> Play Stimulus at equal intensity LED values"); 
          Serial.println("b -> Play Stimulus at Natural Statistics max power");  
          break; 
          
// ##################################################################################          
      }
    }
  }
}

void update_cols() {
    stred   =     pgm_read_byte_near(arrayR + ArrayPosition);   // Set Red LED values
    stgreen =     pgm_read_byte_near(arrayG + ArrayPosition);   // Set Green LED values
    stblue  =     pgm_read_byte_near(arrayB + ArrayPosition);   // Set Blue LED value
    stuv    =     pgm_read_byte_near(arrayU + ArrayPosition);   // Set UV LED values

    LED(Red,stred);        // update the Red LED value
    LED(Green,stgreen);    // update the Grenn LED value
    LED(Blue,stblue);      // update the Blue LED value
    LED(UV,stuv);          // update the UV LED value
}

// Play stimulus function at LED "Full power"
void  PlayArrays () { 
/* Feeding LED values according to the current position array */

   update_cols();

  /* Trigger ------------------------------------------------------------------------*/
  if (PulseCount < Trigger_dur){      // Determine Trigger_pulse duration
    digitalWrite(pSyncOut,1);         // Set Trigeer output to 1
  }
  else {                              // Once Trigger duration reached
    digitalWrite(pSyncOut,0);         // Set Trigger output to 1
  }

  
  /* Moving Through the stimulus ----------------------------------------------------*/
  
  PulseCount += 1;      // Pulse Couter, move to the next pulse

  if(PulseCount == (PulseArray [ArrayPosition])){    // When the pulse counter reaches the current position array duration 
    ArrayPosition += 1;                                              // Move to the next position array
    PulseCount = 0;                                                  // Reset the pulse counter
  } 
  
//  if (iLoop == 0 && ArrayPosition == 1 && PulseCount ==0){
//    Serial.println("Loop 1");
//  }
 
  if(ArrayPosition == nArrayEntries){     // When current iLoop has reached the last ArrayPosition
    iLoop += 1;                           // Move to the next loop
    ArrayPosition = 1;                    // Reset the position array and skip the preadaptation (ArrayPosition = 0)

  }

  if(iLoop == nLoops){                                   // When Array has completed its last loop
    detachInterrupt(digitalPinToInterrupt(pBlank));      // Stop blanking signal  
    Play0();                                             // Turn off all LEDs
    PulseCount = 0;                                      // Reset Pulse Counter
    ArrayPosition = 0;                                   // Reset Array Counter   
    iLoop = 0;                                           // Reset Loop Counter 
    Serial.println(" ...Done");                          // End of stimulus print   
  }
}
//
//    if(iLoop<=nLoops-1){
//      Serial.print("Loop ");
//      Serial.println(iLoop+1);
//    }
