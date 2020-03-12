/* 
 Main LED Part WS2812B - LED
 
 Add Additional Comments Here
 
*/
// _____________Libraries_____________
#include "FastLED.h"

//_____________Macros_____________
#define NUM_LEDS 100
#define DATA_PIN 2
#define TWO_HUNDRED_PI 628
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 255 
#define TRANSITION_DIM 2

//_____________Variable Declarations_____________
CRGB leds[NUM_LEDS];            // Array to indicate LEDs in sequence

bool debugMode = true;          // Debugging to the STDIO/Serial Monitor

int brakeButton = 2;            // Interrupt

int element = 0;                // An element is an led defined by a sequential number
int last_element = 0;           // The very last element initialised in the method

bool dimState = true;           // The current brightness state
bool startupValue = true;       // For the animation

//_____________Setup_____________
void setup()
{ 
    pinMode(brakeButton, INPUT_PULLUP);
    pinMode(brakeButton, INPUT_PULLUP);     //pinMode is setup
    
    attachInterrupt(digitalPinToInterrupt(brakeButton),brakePressedISR, RISING);  //Interrupt
    attachInterrupt(digitalPinToInterrupt(brakeButton), brakeReleasedISR, FALLING);
    
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);                                //delay for LED before turning on. 
    Serial.begin(9600);  // Sets up the serial baud = 9600
}

//_____________Main_____________
void loop() 
{  
  if(startupValue == true)
  {
    startUpLEDAnimation(startupValue);
    startupValue = false;
  }

  if(dimState == true)
  {
    dimLEDS(dimState); // Keep Light Dim
    dimState = false;
  }
}


//_____________Interrupt Service Routines_____________

// Whenever the brake is pressed the light is set to maximum brightness gradually.
// Args: None
void brakePressedISR() 
{
    for(int i = 255; i >= 64; i--)
    {
      FastLED.setBrightness(i);
      FastLED.show();
      delay(TRANSITION_DIM);
    }
    debug("BrakePressedISR");
}


// When the brake is released the light is set to the minimum brightness
// Args: None
void brakeReleasedISR()
{
    dimLEDS(true);
    debug("BrakeReleasedISR");
}

//_____________LED Control_____________

// Reduces the brights to minimum brightness
// Args: Boolean value for the state of dimming
void dimLEDS(bool dimState) 
{
  for(int i = MAX_BRIGHTNESS; i >= MIN_BRIGHTNESS; i--)
  {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(TRANSITION_DIM);
  }
  debug("Dimming Complete");  
}

// Turns on the lights sequentially
// Args: Boolean value for the state for the startup
void startUpLEDAnimation(bool startupValue) 
{
      for(int i=0; i<TWO_HUNDRED_PI; i++)
      {
        
        element = round((NUM_LEDS-1)/2*(sin(i/100.0)+1));
        leds[element].g = 255;
        FastLED.show();
        delay(1);
        if(element < last_element)
        {
            leds[element].g = 0;
            FastLED.show();
        }
        last_element = element;
      }   
      debug("Startup LED Animation Complete");  
}


//_____________Debugging_____________

// Outputs on the STDIO or Serial Monitor
// Args: String type
void debug(String response)
{
  if(debugMode == true)
  {
     Serial.println(response);
  }
}
