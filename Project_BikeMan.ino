#include <Adafruit_NeoPixel.h>
#include <EnableInterrupt.h>

//Macros
#define ARDUINOPIN 12
#define FILTER 1
#define NB_PIX 100
#define LED_PIN 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NB_PIX, LED_PIN, NEO_GRB + NEO_KHZ800);

// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int value2 = 0;

; //4 is about one notch per LED, 6 is about 2 notches
bool flip = false;
void interruptFunction() {
  value2++;
  //    Serial.print(value2);
}


void setup() {
  //  Serial.begin(9600);
  enableInterrupt(ARDUINOPIN, interruptFunction, CHANGE);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //  strip.
}

void loop() {
  static uint8_t value;
  //value2++;
  //  Serial.print("Pin was interrupted: ");
  //  Serial.print(value2);
  //  Serial.println(" times so far.");

  if (value2 >= FILTER)
  {
    strip.setPixelColor(value, strip.Color(0, 255, 0)); //GREEN

    strip.show();
    value++;
    value2 = 0;
  }

  if (value > NB_PIX)
  {
    //            rainbowCycle(10); // cycles of different colours (like a LGBQT flag) more segmented than just rainbow
    //        rainbow(300); //about 5 seconds of slow rainbow with slower/smoother transitions
    //  delay(5000);


    value = 0;
    value2 = 0;
    flip = !flip;
  }
  if (value == 0)
  {
    if (flip == true)
      colorWipe(strip.Color(255, 0, 0), 0); // Red
    if (flip == false)
      colorWipe(strip.Color(0, 0, 255), 0); // Blue
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < NB_PIX; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
