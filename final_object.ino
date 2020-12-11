#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NUMPIXELS      15

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800);


int soundLevel = 0;
int delayval = 0; // delay for half a second


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbowCycle(uint8_t wait){
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait, int level) {
  uint16_t i, j;

  for(j=0; j<level; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  soundLevel = analogRead(A0);
  Serial.println(soundLevel);

  if( (soundLevel > 20 ) && (soundLevel <= 50)){
    pixels.clear();
    for(int i=0;i<=11;i++){
    
  
    pixels.setPixelColor(i, pixels.Color(153,0,204)); 
    //make leds purple
  }
  pixels.show(); // This sends the updated pixel color to the hardware. 
  delay(delayval);
  
  }

  //////////////////////////////////////////
//  if( (soundLevel > 30) && (soundLevel <= 38)){
//    pixels.clear();
//    rainbow(10, 100);
//
//  
//  }
    //////////////////////////////////////
//    if( (soundLevel > 38) && (soundLevel <= 45)){
//      pixels.clear();
//      rainbow(10, 100);
//
//  }

  ///////////////////////////////////////////////////////
//  
//  if( (soundLevel > 10)&& (soundLevel <= 11)){
//    pixels.clear();
//    rainbow(10, 150);
//
//  }

/////////////////////////////////////////////////////////////////

//   if( (soundLevel > 11) && (soundLevel <= 13)){
//    pixels.clear();
//    rainbow(10, 200);
//
//  
//  }
////////////////////////////////////////////////////////////////
     if( (soundLevel > 50) && (soundLevel < 2000)){
      rainbow(10, 255);
      pixels.clear();


     }
}
