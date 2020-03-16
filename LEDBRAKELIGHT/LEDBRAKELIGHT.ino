/* 
 Main LED Part WS2812B - LED
 
 Add Additional Comments Here
 
*/
// _____________Libraries_____________
#include "FastLED.h"

//_____________Macros_____________
#define NUM_LEDS 45
#define DATA_PIN 2
#define TWO_HUNDRED_PI 628
#define MIN_BRIGHTNESS 32
#define MAX_BRIGHTNESS 255 
#define TRANSITION_DIM 2

//_____________Variable Declarations_____________
CRGB leds[NUM_LEDS];            // Array to indicate LEDs in sequence

bool debugMode = true;          // Debugging to the STDIO/Serial Monitor
bool repeat = true;            // Light Testing

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
    
    //attachInterrupt(digitalPinToInterrupt(brakeButton),brakePressedISR, RISING);  //Interrupt
    //attachInterrupt(digitalPinToInterrupt(brakeButton), brakeReleasedISR, FALLING);
    
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);                                //delay for LED before turning on. 
//    setMaxRefreshRate(30, true);
    Serial.begin(9600);  // Sets up the serial baud = 9600
}

//_____________Main_____________
void loop() 
{
  if(debugMode and repeat)
  {
    checkLightStatus();
    repeat = false;
  }
 
  if(startupValue == true)
  {
    startUpLEDAnimation();
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
void startUpLEDAnimation() 
{
      for(int i=0; i<TWO_HUNDRED_PI; i++)
      {
        
        element = round((NUM_LEDS-1)/2*(sin(i/100.0)+1));
        FastLED.show();
        if(element < last_element)
        {
            leds[element].g = 64;
            delay(10); // Start Up Delay
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


// Tests all LEDs brightness and their colours
// Args: None
void checkLightStatus()
{
  brightnessTest();
  delay(1000);
  colourTest();  
}


// Tests The Colours
// Args: None
void colourTest()
{
  delay(100);
  Serial.println("Colour Check");
  
  // Colour Check 

  for(int colour = 0; colour < 255; colour++ )
  {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds[i].b = colour; 
      }
      FastLED.show();
      delay(TRANSITION_DIM);
      
  }
  
  for(int colour = 0; colour < 255; colour++ )
  {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds[i].r = colour; 
      }
      FastLED.show();
      delay(TRANSITION_DIM);
      
  }

  for(int colour = 0; colour < 255; colour++ )
  {
      for(int i = 0; i < NUM_LEDS; i++)
      {
        leds[i].g = colour; 
      }
      FastLED.show();
      delay(TRANSITION_DIM);
      
  }

  Serial.println("Colour Test Complete");
  delay(100);
  Serial.println("Switching Off LEDs");
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  delay(2000);
}

// Tests The Brightness
// Args: None
void brightnessTest()
{
  // Brightness Check
  delay(100);
  // Lowest Brightness
  FastLED.setBrightness(0);
  FastLED.show();
  
  // Increment Brightness 

  // Set Colour
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].r = 64;
    leds[i].g = 64;
    leds[i].b = 64;
  }
  // Alter Brightness
  Serial.println("Brightness Test");
  for(int i = 0; i < 255; i++) 
  {
    FastLED.setBrightness(i);
    delay(TRANSITION_DIM);
    FastLED.show();
  }
  delay(1000);
}
