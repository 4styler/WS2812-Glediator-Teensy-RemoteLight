//Merged from:
//https://github.com/PaulStoffregen/WS2812Serial and
//from pjrc forum

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 10

// Which pin are you use?
// Usable pins:
//   Teensy LC:   1, 4, 5, 24 (You can connect one of these Pins to Pin 17 to get 5v on Pin "17 vin Voltage"
                  //https://www.pjrc.com/teensy/teensyLC.html or https://github.com/PaulStoffregen/WS2812Serial (See Picture))
//   Teensy 3.2:  1, 5, 8, 10, 31   (overclock to 120 MHz for pin 8)
//   Teensy 3.5:  1, 5, 8, 10, 26, 32, 33, 48
//   Teensy 3.6:  1, 5, 8, 10, 26, 32, 33
//   Teensy 4.0:  1, 8, 14, 17, 20, 24, 29, 39
//   Teensy 4.1:  1, 8, 14, 17, 20, 24, 29, 35, 47, 53

#define DATA_PIN 24


#define COLOR_ORDER GRB
#define BRIGHTNESS  255
#define BAUD_RATE 1000000 //115200  //1000000  //250000   // Set the same in Glediator
#define CMD_NEW_DATA 1

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(BAUD_RATE);
  delay(1500);  // startup delay
  LEDS.addLeds<WS2812SERIAL,DATA_PIN,BGR>(leds,NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);
  
}

int serialGlediator() {
  while (!Serial.available()) {}
  return Serial.read();
}

byte r,g,b;
int i;

void loop() {
   while (serialGlediator () != CMD_NEW_DATA) {}
       Serial.readBytes((char*)leds, NUM_LEDS * 3);
       FastLED.show();
   }                                   

void startupLEDsTest() {
  // startup blink test to confirm LEDs are working.
  FastLED.setBrightness(32);
  fill_solid(leds, NUM_LEDS, CRGB(255,0,0));  // fill red
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB(0,255,0));  // fill green
  FastLED.show();
  delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB(0,0,255));  // fill blue
  FastLED.show();
  delay(1000);
  FastLED.clear();
  FastLED.show();
  FastLED.setBrightness(BRIGHTNESS);
}
