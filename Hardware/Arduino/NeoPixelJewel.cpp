#include <Adafruit_NeoPixel.h>

#define DELAYMS 50
#define BRIGHTNESS 20

using namespace std;

class NeoPixelJewel
{
  private:
    Adafruit_NeoPixel neoPixelJewel;

  public:
    NeoPixelJewel(int16_t pin, uint16_t numPixels, neoPixelType type)
    {
      neoPixelJewel = Adafruit_NeoPixel(numPixels, pin, type);
    }

    void initialize() {
      neoPixelJewel.begin();
      neoPixelJewel.setBrightness(BRIGHTNESS);
    }

    void waitUntilAvailable() {
      if(!neoPixelJewel.canShow()) {
        delay(DELAYMS);
      }
    }

    void turnOff()
    {
      waitUntilAvailable();
      neoPixelJewel.clear();
      neoPixelJewel.show();
    }

    void turnOn()
    {
      waitUntilAvailable();
      for( int i = 0; i < neoPixelJewel.numPixels(); i++ )
        neoPixelJewel.setPixelColor (i, 255, 255, 255);
      neoPixelJewel.show();
    }

    void turnOn(uint8_t r, uint8_t g, uint8_t b)
    {
      waitUntilAvailable();
      for( int i = 0; i < neoPixelJewel.numPixels(); i++ )
        neoPixelJewel.setPixelColor (i, r, g, b);
      neoPixelJewel.show(); 
    }
};