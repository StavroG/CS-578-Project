#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define DELAYMS 75
#define INTEGRATION_TIME TCS34725_INTEGRATIONTIME_50MS
#define GAIN TCS34725_GAIN_4X

using namespace std;

class HiLetgoRGBColorSensor 
{
  private:
	Adafruit_TCS34725 sensor;
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t c;
	uint16_t colorTemp;
	uint16_t lux;
  public:
    HiLetgoRGBColorSensor(uint8_t integrationTime, tcs34725Gain_t gain)
    {
		sensor = Adafruit_TCS34725(integrationTime, gain);
    }

    bool initialize() {
		return sensor.begin;
    }

    int read()
    {
		getRawData();
		colorTemp = calculateColorTemperature();
		lux = calculateLux(r,g,b);
    }
	
	void setIntegrationTime(uint8_t it) {
		sensor.setIntegrationTime(it);
	}
	
	void setGain(tcs34725Gain_t gain) {
		sensor.setGain(gain);
	}
	
	void getRawData() {
		sensor.getRawData(&r, &g, &b, &c);
	}
	
	void getRawDataOneShot() {
		sensor.getRawDataOneShot(&r, &g, &b, &c);
	}
	
	void getRGB() {
		sensor.getRawData(&r, &g, &b);
	}
	
	uint16_t getR() {
		return r;
	}
	
	uint16_t getG() {
		return g;
	}
	
	uint16_t getB() {
		return b;
	}
	
	uint16_t getC() {
		return c;
	}
	
	uint16_t getColorTemp() {
		return colorTemp;
	}
	
	uint16_t getLux() {
		return lux;
	}
	
	uint16_t calculateColorTemperature() {
		return sensor.calculateColorTemperature_dn40(r,g,b);
	}
	
	uint16_t calculateColorTemperature_dn40() {
		return sensor.calculateColorTemperature_dn40(r,g,b,c);
	}
	
	uint16_t calculateLux() {
		return sensor.calculateLux(r, g, b);
	}
	
	void setInterrupt(boolean i) {
		sensor.setInterrupt(i);
	}
	
	void clearInterrupt() {
		sensor.clearInterrupt();
	}
	
	void setIntLimits(uint16_t low, uint16_t high) {
		sensor.setIntLimits(low,high);
	}
	
};