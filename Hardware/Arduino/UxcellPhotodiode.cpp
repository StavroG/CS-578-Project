#include "Arduino.h"

#define DELAYMS 75

using namespace std;

class UxcellPhotodiode
{
  private:
	int inputPin;
    bool sensorMode; //0 - digital : 1- analog

  public:
    UxcellPhotodiode(int16_t pin, bool mode)
    {
		inputPin = pin;
		sensorMode = mode;
    }

    void initialize() {
		pinMode(inputPin, INPUT);
    }

    int read()
    {
		delay(DELAYMS);
		if(sensorMode == 0)
			return digitalRead(inputPin);
		else
			return analogRead(inputPin);
    }
	
};