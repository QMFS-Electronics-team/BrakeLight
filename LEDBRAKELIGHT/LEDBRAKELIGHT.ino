// WS2812B - LED STRIP
// Initial State OFF
// IF NO SIGNAL LIGHT SHOULD BE DIM AT 10 LEVELS
// IF THERE IS A SIGNAL LIGHT SHOULD BE AT 244 LEVEL.

#include "FastLED.h"
 
#define NUM_LEDS 100
#define DATA_PIN 2
#define TWO_HUNDRED_PI 628
 
CRGB leds[NUM_LEDS];

int interruptBrakePressed = 2;  // Interrupt
int startupValue = 0;           // For the animation
int element = 0;                // An element is an led defined by a sequential number
int last_element = 0;           // The very last element initialised in the method


void setup()  
{ 
    Serial.begin(9600); // Sets up the serial baud = 9600
    pinMode(interruptBrakePressed, INPUT_PULLUP); //pinMode is setup
    attachInterrupt(digitalPinToInterrupt(interruptBrakePressed),brakePressedISR, CHANGE); //interrupt
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  //delay for LED before turning on. 
}

void loop() // Main
{

    if(startupValue == 0) // Start Animation
    {
      startUpLEDAnimation(startupValue);
      counter ++; // Increment of counter will precent the animation from occurring again
    }

    
    dimLEDS(); // Keep Light Dim
}

void brakePressedISR() // Whenever the brake is pressed the light is set to 64 levels brightness gradually.
{
    for(int i = 32; i >= 64; i++)
    {
      Serial.println(i);
      FastLED.setBrightness(i);
      FastLED.show();
      delay(10);
    }
}


void dimLEDS() // Reduces the brights to 32 levels with a transition.
{
    Serial.println("dimLEDS");
    //for(int i = 64; i >= 32; i--)
    for(int i = 64; i >= 64; i--)
    {
      Serial.println(i);
      FastLED.setBrightness(i);
      FastLED.show();
      delay(50);
      
    }
}


void startUpLEDAnimation(int startupValue) // Turns on the lights sequentially
{
  Serial.println("startUpLEDAnimation");
  
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

  Serial.println("endingstartUpLEDAnimation");

  
}  



  
