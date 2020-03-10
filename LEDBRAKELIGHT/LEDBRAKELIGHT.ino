// WS2812B - LED STRIP


// Libraries
#include "FastLED.h"


// Macros
#define NUM_LEDS 45
#define DATA_PIN 2
#define TWO_HUNDRED_PI 628



// Global Variables
CRGB leds[NUM_LEDS];            // Array to indicate LEDs in sequence
bool debugMode = true;
int interruptBrakePressed = 2;  // Interrupt
int startupValue = 0;           // For the animation
int element = 0;                // An element is an led defined by a sequential number
int last_element = 0;           // The very last element initialised in the method

// Setup
void setup()
{ 
    Serial.begin(9600);                                                                     // Sets up the serial baud = 9600
    pinMode(interruptBrakePressed, INPUT_PULLUP);                                           //pinMode is setup
    attachInterrupt(digitalPinToInterrupt(interruptBrakePressed),brakePressedISR, CHANGE);  //interrupt
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);                                //delay for LED before turning on. 
}

// Main
void loop() 
{
  leds[5].g = 32;
  FastLED.show();

  /*
  for(int i = 0; i < 54; i++)
  {
    
    FastLED.show();
  }
  delay(10000);
  */
  /*
    if(startupValue == 1) // Start Animation
    {
      startUpLEDAnimation(0);
      startupValue ++; // Increment of counter will precent the animation from occurring again
    }
    dimLEDS(); // Keep Light Dim

    */
}

// Whenever the brake is pressed the light is set to 64 levels brightness gradually.
void brakePressedISR() 
{
    debug("Brake has been pressed");
    for(int i = 32; i >= 64; i++)
    {
      Serial.println(i);
      FastLED.setBrightness(i);
      FastLED.show();
      delay(10);
    }
}

// Reduces the brights to 32 levels with a transition.
void dimLEDS() 
{
    debug("Diming LEDs");
    for(int i = 64; i >= 64; i--)
    {
      Serial.println(i);
      FastLED.setBrightness(i);
      FastLED.show();
      delay(50);
    }
    debug("Dimming Complete");
}

// Turns on the lights sequentially
void startUpLEDAnimation(int startupValue) 
{
  debug("Startup LED Animation");
  if(startupValue > 0)
  {

      for(int i=0; i<TWO_HUNDRED_PI; i++)
      {
        
        element = round((NUM_LEDS-1)/2*(sin(i/100.0)+1));
        leds[element].g = 255;
        FastLED.show();
         
        delay(1);
         
        if(element < last_element){
            leds[element].g = 0;
            FastLED.show();
        }
         
        last_element = element;
      }   
  }
  debug("Startup LED Animation Complete");
}  


void debug(String response)
{
  if(debugMode == true)
  {
     Serial.println("From Debug");
     Serial.println(response);
  }
}
