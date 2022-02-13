#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 60

// Which pin are you use?
// Usable pins:
//   Teensy LC:   1, 4, 5, 24
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
  startupLEDsTest();
}

int serialGlediator() {
  while (!Serial.available()) {}
  return Serial.read();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

byte r,g,b;
int i;

void noserial() {
  static uint8_t hue = 0;
     Serial.print("x");
      // First slide the led in one direction
      for(int i = 0; i < NUM_LEDS; i++) {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall();
        // Wait a little bit before we loop around and do it again
        delay(20);
      }
      Serial.print("x");
    
      // Now go in the other direction.
      for(int i = (NUM_LEDS)-1; i >= 0; i--) {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall();
        // Wait a little bit before we loop around and do it again
        delay(20);
      }
  
}

void loop() {
  
   while (!Serial.available()) {
     noserial();
   }
   
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
