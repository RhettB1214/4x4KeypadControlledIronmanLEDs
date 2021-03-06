#include <Adafruit_NeoPixel.h>
#include <FastLED_NeoPixel.h>
#include <FastLED.h>
#include <Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad
bool Rainbow;
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );
#define pin 6
#define ledCount 12
#define pinp 3
#define ledCountp 24
#define basePin 5
#define baseLEDs 36
CRGB leds [baseLEDs];
FastLED_NeoPixel_Variant base(leds, baseLEDs);
FastLED_NeoPixel <ledCount, pin, NEO_RGB + NEO_KHZ800> pixels;
FastLED_NeoPixel <ledCountp, pinp, NEO_RGB + NEO_KHZ800> strip;




int delayval = 100; // timing delay in milliseconds
uint32_t off = pixels.Color(0, 0, 0);
uint32_t blue = pixels.Color(28, 28, 255);
uint32_t purple = pixels.Color(255, 0, 255);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t white = pixels.Color(200, 200, 200);
uint32_t offp = strip.Color(0, 0, 0);
uint32_t bluep = strip.Color(28, 28, 255);
uint32_t purplep = strip.Color(255, 0, 255);
uint32_t redp = strip.Color(255, 0, 0);
uint32_t whitep = strip.Color(200, 200, 200);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t greenp = strip.Color(0, 255, 0);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t yellowp = strip.Color(255, 255, 0);
uint32_t lightPink = pixels.Color(252, 100, 151);
uint32_t lightPinkp = strip.Color(252, 100, 151);
uint32_t lightPurple = pixels.Color(94, 41, 89);
uint32_t lightPurplep = strip.Color(94, 41, 89);
uint32_t lightGreen = pixels.Color(65, 112, 62);
uint32_t lightGreenp = strip.Color(65, 112, 62);
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
uint32_t Wheelp(byte WheelpPos) {
  if (WheelpPos < 85) {
    return strip.Color(WheelpPos * 3, 255 - WheelpPos * 3, 0);
  }
  else if (WheelpPos < 170) {
    WheelpPos -= 85;
    return strip.Color(255 - WheelpPos * 3, 0, WheelpPos * 3);
  }
  else {
    WheelpPos -= 170;
    return strip.Color(0, WheelpPos * 3, 255 - WheelpPos * 3);
  }
}
void setup()
{
  pinMode(36, OUTPUT);
  Serial.begin(9600);
  pixels.begin();
  pixels.show();
  strip.begin();
  strip.show();
  pixels.setBrightness(127);
  strip.setBrightness(127);

}
void rainbow(int wait) {
  uint16_t i, j, n;
  Rainbow = true;
 while(Rainbow == true){
  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i * 1 + j) & 255));
    }
    for (n = 0; n < strip.numPixels(); n++) {
      strip.setPixelColor(n, Wheelp((n * 1 + j) & 255));
    }
    strip.show();
    pixels.show();
    delay(wait);
    if (keypad.getKey() != NO_KEY) {
          Serial.println("key pressed; breaking out of loop");
          Rainbow = false;
         break;
        }
  }
  
 }
}


long unsigned int color_a;
long unsigned int color_b;
void loop() {
    analogWrite(36, 255);

  char input = keypad.getKey();
  if (input != NO_KEY) {
    Serial.println(input);
  }

  int y = 0;
  switch (input) {

    case '1':
     // color_a = blue;
    //  color_b = bluep;
    digitalWrite(36, HIGH);
      break;

    case '2':
      color_a = red;
      color_b = redp;
      break;

    case '3':
      color_a = purple;
      color_b = purplep;
      break;

    case '4':
      color_a = white;
      color_b = whitep;
      break;

    case '5':
      color_a = green;
      color_b = greenp;
      break;

    case '6':
      color_a = yellow;
      color_b = yellowp;
      break;

    case '7':
      color_a = lightPink;
      color_b = lightPinkp;
      break;

    case '8':
      color_a = lightPurple;
      color_b = lightPurplep;
      break;

    case '9':
      color_a = lightGreen;
      color_b = lightGreenp;
      break;

    case 'A':
      pixels.fill(color_a, 0, 12);
      pixels.show();
      Serial.println("Chest On");
      break;

    case 'B':
      for (int x = 1; x <= ledCount; x++) {
        pixels.fill(color_a, 0, x);
        pixels.show();
        delay(250); 
      }
      break;

    case 'C':
      while (keypad.getKey() == NO_KEY) {

        pixels.setPixelColor(y, color_a);
        pixels.show();
        pixels.setPixelColor(y - 1, off);
        pixels.show();
        delay(100);

        if (y == ledCount) {
          y = 0;
        } else {
          y++;
        }

      }

      break;

    case '*':
      strip.fill(color_b, 0, ledCountp);
      strip.show();
      Serial.println("Palm On");
      break;

    case '0':
      while (keypad.getKey() == NO_KEY) {
        strip.fill(color_b, 0, ledCountp);
        strip.show();
        Serial.println("about to delay for 60 seconds");
        int loopCounter = 0;
        while (keypad.getKey() == NO_KEY && loopCounter <= 6000) {
          loopCounter += 1;
          delay(10);
        }
        if (keypad.getState() == PRESSED) {
          Serial.println("key pressed; breaking out of loop");
          break;
        }
        strip.fill(offp, 0, ledCountp);
        strip.show();
        delay(100);
        strip.fill(color_b, 0, ledCountp);
        strip.show();
        delay(100);
        strip.fill(offp, 0, ledCountp);
        strip.show();
        delay(100);
        strip.fill(color_b, 0, ledCountp);
        strip.show();
        delay(100);
        strip.fill(offp, 0, ledCountp);
        strip.show();
        delay(100);
        strip.fill(color_b, 0, ledCountp);
        strip.show();
        Serial.println("looping");
      }
      Serial.println("leaving loop");
      break;

    case '#':
      while (keypad.getKey() == NO_KEY) {
        rainbow(10);
     if (Rainbow == false){
      break;
     }
      }
      Serial.println("Rainbow Loop left");
      break;

    case 'D':
      strip.fill(offp, 0, ledCountp);
      pixels.fill(off, 0, ledCount);
      pixels.show();
      strip.show();
      Serial.println("LEDs Off");
      break;
  }
}
