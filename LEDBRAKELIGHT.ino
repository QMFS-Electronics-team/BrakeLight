// WS2812B - LED STRIP
// Initial State OFF
// IF NO SIGNAL LIGHT SHOULD BE DIM AT 10 LEVELS
// IF THERE IS A SIGNAL LIGHT SHOULD BE AT 244 LEVEL.

#include "FastLED.h"
 
#define NUM_LEDS 39
#define DATA_PIN 5
#define TWO_HUNDRED_PI 628
 
CRGB leds[NUM_LEDS];

int interruptBrakePressed = 2; 

 
int counter = 0;
int element = 0;
int last_element = 0;
int currentState = 1; // For dim and initial
   


void setup() { 
    Serial.begin(9600);
    delay(3000);
    pinMode(interruptBrakePressed, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPinR),brakePressedISR, CHANGE);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {

    if(counter == 0) // Start Animation
    {
      startUpLEDAnimation();
      counter ++;
    }

    if(currentState == 0)
    {
      // If a button is pressed
      // Light Up Break Ligt with interrupt
    }
    else
    {
      // Keep Light Dim
      dimLEDS();
      currentState = 0;
    }

    
}

void brakePressedISR()
{
    for(int i = 32; i >= 64; i++)
    {
      Serial.println(i);
      FastLED.setBrightness(i);
      FastLED.show();
      delay(10);
    }
}


void dimLEDS()
{
    Serial.println("dimLEDS");
    for(int i = 64; i >= 32; i--)
    {
      Serial.println(i);
      FastLED.setBrightness(i);
      FastLED.show();
      delay(50);
      
    }

    delay(1000);
    
    
    
}


void startUpLEDAnimation()
{
  Serial.println("startUpLEDAnimation");
   
  for(int i=0; i<TWO_HUNDRED_PI; i++){
      element = round((NUM_LEDS-1)/2*(sin(i/100.0)+1));
      leds[element].g = 64;
      FastLED.show();
       
      delay(1);
       
      if(element < last_element){
          leds[element].g = 0;
          FastLED.show();
      }
       
      last_element = element;
  }
  
}  



  
