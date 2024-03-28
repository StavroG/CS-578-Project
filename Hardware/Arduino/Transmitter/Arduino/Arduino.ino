#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\NeoPixelJewel.cpp"

//NeoPixelJewel
//https://github.com/adafruit/Adafruit_NeoPixel
#define LED_PIN 3
#define NUM_PIXELS 7
#define TYPE NEO_RGBW + NEO_KHZ800

using namespace std;

NeoPixelJewel led = NeoPixelJewel(LED_PIN, NUM_PIXELS, TYPE);

void setup() {
  led.initialize();
}

void loop() {
  led.turnOn();
  led.turnOff();
  led.turnOn(255,0,0);
  led.turnOn(0,255,0);
  led.turnOn(0,0,255);
}