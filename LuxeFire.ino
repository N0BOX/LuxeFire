#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 17
//#define DEBUG

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
#ifdef DEBUG
  Serial.begin(115200);
  while(!Serial) {}
#endif
}

void loop() {
  
  uint8_t iRandomRed = random(164, 255);
  uint8_t iRandomGrn = random(82, 127);
  uint8_t iRandomBlu = random(0, 255);
  uint8_t iRandomDivisor = random(1, 32);
#ifdef DEBUG
  Serial.print("Red: ");
  Serial.print(iRandomRed / iRandomDivisor, DEC);
  Serial.print("  Green: ");
  Serial.print(iRandomGrn / iRandomDivisor, DEC);
  Serial.print("  Blue: ");
  //Serial.print(iRandomBlu / iRandomDivisor, DEC);
  //Serial.print("  Divisor: ");
  Serial.println(iRandomDivisor, DEC);
#endif
  colorWipe(strip.Color((iRandomRed / iRandomDivisor), (iRandomGrn / iRandomDivisor), 0), 10); // Orange?
  //delay(2);
}

void colorFade(uint16_t pixel, uint32_t clrStart, uint32_t clrEnd, uint8_t iStep, uint8_t iNumSteps)
{
  uint8_t clrRedStart = 0;
  uint8_t clrGrnStart = 0;
  uint8_t clrBluStart = 0;
  uint8_t clrRedEnd = 0;
  uint8_t clrGrnEnd = 0;
  uint8_t clrBluEnd = 0;
  int clrRedStep = 0;
  int clrGrnStep = 0;
  int clrBluStep = 0;
  unpackColors(clrStart, clrRedStart, clrGrnStart, clrBluStart);
  unpackColors(clrStart, clrRedEnd, clrGrnEnd, clrBluEnd);
  clrRedStep = (clrRedEnd - clrRedStart) / iNumSteps;
  clrGrnStep = (clrGrnEnd - clrGrnStart) / iNumSteps;
  clrBluStep = (clrBluEnd - clrBluStart) / iNumSteps;
  strip.setPixelColor(pixel, packColors((clrRedStart + (iStep * clrRedStep)), (clrGrnStart + (iStep * clrGrnStep)), (clrBluStart + (iStep * clrBluStep))));
  //strip.show();  // Probably don't want to do this unless you aren't changing any other Neopixels each time this function is called.
}

void unpackColors(uint32_t c, uint8_t &r, uint8_t &g, uint8_t &b)
{
  r = (uint8_t)(c >> 16),
  g = (uint8_t)(c >>  8),
  b = (uint8_t)c;
}

uint32_t packColors(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
