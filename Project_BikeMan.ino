#include <Adafruit_NeoPixel.h>
#define NbPix 9
#define LedPin 12
#define SwitchPin 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NbPix, LedPin, NEO_GRB + NEO_KHZ800);

bool SwitchState = false;

// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int value = 0;
volatile int value2 = 0;
int filter = 10;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(255, 0, 0), 10); // Red
  // sets the digital pin as input
  pinMode(SwitchPin, INPUT);
}

void loop() {
  if (digitalRead(SwitchPin) == true)
  {
    SwitchState = false;

    for (uint16_t i = 0; i <= value; i++)
    {
      strip.setPixelColor(i, strip.Color(0, 255, 0));
      strip.show();
      delay(1);
    }
    value2++;
    if (value2 == filter)
    {
      value++;
      if (value > NbPix)
      {
        value = 0;
        colorWipe(strip.Color(255, 0, 0), 10); // Red
      }
      value2 = 0;
    }


  }


}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

