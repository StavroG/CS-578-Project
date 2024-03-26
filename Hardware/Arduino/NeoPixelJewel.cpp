#include <Adafruit_NeoPixel.h>

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
      neoPixelJewel.setBrightness(255);
    }

    void turnOff()
    {
        neoPixelJewel.clear();
        neoPixelJewel.show();
    }

    void turnOn()
    {
      for( int i = 0; i < neoPixelJewel.numPixels(); i++ )
        neoPixelJewel.setPixelColor (i, 255, 255, 255);
      
      neoPixelJewel.show();
    }

    void turnOn(uint8_t r, uint8_t g, uint8_t b)
    {
      for( int i = 0; i < neoPixelJewel.numPixels(); i++ )
        neoPixelJewel.setPixelColor (i, r, g, b);  
      neoPixelJewel.show();
    }
};