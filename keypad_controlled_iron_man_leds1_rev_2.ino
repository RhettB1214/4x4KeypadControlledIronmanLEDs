#include <Keypad.h>

#include <Adafruit_NeoPixel.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

Adafruit_NeoPixel pixels(12, 6);
Adafruit_NeoPixel pixelsp(14, 3);

int delayval = 100; // timing delay in milliseconds
uint32_t off = pixels.Color(0, 0, 0);
uint32_t blue = pixels.Color(51, 153, 255);
uint32_t purple = pixels.Color(255, 0, 255);
uint32_t red = pixels.Color(255, 0, 0);
uint32_t white = pixels.Color(200, 200, 200);
uint32_t offp = pixelsp.Color(0, 0, 0);
uint32_t bluep = pixelsp.Color(51, 153, 255);
uint32_t purplep = pixelsp.Color(255, 0, 255);
uint32_t redp = pixelsp.Color(255, 0, 0);
uint32_t whitep = pixelsp.Color(200, 200, 200);
uint32_t green = pixels.Color(0, 255, 0);
uint32_t greenp = pixels.Color(0, 255, 0);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t yellowp = pixels.Color(255, 255, 0);
void setup()
{
  Serial.begin(9600);
  pixels.begin();
  pixels.show();

}


  long unsigned int color_a;
  long unsigned int color_b;
void loop(){

  char input = keypad.getKey();
  if (input != NO_KEY) {
    Serial.println(input);
  }
  
    int y = 0;
  switch (input) {
    
    case '1':
    color_a = blue;
    color_b = bluep;
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
    
    case 'A':
    pixels.fill(color_a, 0, 12);
    pixels.show();
    break;
    
    case 'B':
   	 for(int x = 1; x <= 12; x++) {
      pixels.fill(color_a, 0, x);
      pixels.show();
       delay(50); 
     }
    break;
    
    case 'C':
    while(keypad.getKey() == NO_KEY){
      
    pixels.setPixelColor(y, color_a);
    pixels.show();
    pixels.setPixelColor(y - 1, off);
    pixels.show();
    delay(100);  
      
      if(y == 12) {
        y = 0;
      }else{
        y++;
      }
      
    }
   
    break;
    
    case '*':
    pixelsp.fill(color_b,0,14);
    pixelsp.show();
    break;
    
    case '0':
    while (true) {
    pixelsp.fill(color_b,0,14);
    pixelsp.show();
    delay(60000);
    pixelsp.fill(offp, 0, 14);
    pixelsp.show();
    delay(100);
    pixelsp.fill(color_b, 0, 14);
    pixelsp.show();
    }
    break;
    
    case 'D':
    pixelsp.fill(offp,0,14);
    pixels.fill(off, 0, 12);
    pixels.show();
    pixelsp.show();
    break;
  }
}
