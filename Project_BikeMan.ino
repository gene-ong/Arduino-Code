#include <Adafruit_NeoPixel.h>
#include <EnableInterrupt.h>
#define ARDUINOPIN 7



#define NbPix 100
#define LedPin 12

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NbPix, LedPin, NEO_GRB + NEO_KHZ800);

// We need to declare the data exchange
// variable to be volatile - the value is
// read from memory.
volatile int value = 0;
volatile int value2 = 0;
int filter = 1; //4 is about one notch per LED, 6 is about 2 notches

void interruptFunction() {
  value2++;
}


void setup() {
  Serial.begin(9600);
  enableInterrupt(ARDUINOPIN, interruptFunction, CHANGE);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //  strip.
}

void loop() {

  Serial.print("Pin was interrupted: ");
  Serial.print(value2);
  Serial.println(" times so far.");
  //
  //  for (uint16_t i = 0; i < value; i++)
  //  {
  //    strip.setPixelColor(i, strip.Color(0,255, 0));//GREEN
  ////    strip.setPixelColor(i, strip.Color(0,0, 255));//BLUE
  //    strip.show();
  //    delay(1);
  //  }

  if (value2 >= filter)
  {
    strip.setPixelColor(value, strip.Color(0, 255, 0)); //GREEN
    //    strip.setPixelColor(value, strip.Color(0,0, 255));//BLUE
    strip.show();
    value++;
    value2 = 0;
  }
  if (value == 0)
    colorWipe(strip.Color(255, 0, 0), 0); // Red
  if (value > NbPix + 1)
  {
    colorWipe(strip.Color(255, 0, 0), 0); // Red
    value = 0;
  }

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < NbPix; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

