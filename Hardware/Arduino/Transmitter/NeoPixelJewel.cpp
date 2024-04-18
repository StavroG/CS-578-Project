#include <Adafruit_NeoPixel.h>

#define DELAYMS 300
#define BRIGHTNESS 33

#define LED_PIN 3
#define NUM_PIXELS 7
#define TYPE NEO_GRBW + NEO_KHZ800

using namespace std;

class NeoPixelJewel
{
  private:
    Adafruit_NeoPixel neoPixelJewel;

  public:
    NeoPixelJewel()
    {
      neoPixelJewel = Adafruit_NeoPixel(NUM_PIXELS, LED_PIN, TYPE);
    }

    void initialize() {
      neoPixelJewel.begin();
      neoPixelJewel.setBrightness(BRIGHTNESS);
    }

    void turnOff()
    {
      neoPixelJewel.clear();
      neoPixelJewel.show();
	  delay(DELAYMS);
    }

    void turnOn()
    {
	  neoPixelJewel.fill(neoPixelJewel.Color(255, 255, 255),0);
	  neoPixelJewel.show();
	  delay(DELAYMS);
    }

    void turnOn(uint8_t r, uint8_t g, uint8_t b)
    {
	  neoPixelJewel.fill(neoPixelJewel.Color(r, g, b),0);
      neoPixelJewel.show();
	  delay(DELAYMS);
    }
};