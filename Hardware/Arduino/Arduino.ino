#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\NeoPixelJewel.cpp"

using namespace std;

uint16_t LED_PIN = 3;
uint16_t NUM_PIXELS = 7;
neoPixelType TYPE = NEO_GRBW + NEO_KHZ800;

NeoPixelJewel led = NeoPixelJewel(LED_PIN, NUM_PIXELS, TYPE);

void setup() {
  led.initialize();
}

void loop() {
  led.turnOff();
}