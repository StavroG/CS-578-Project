#include "Arduino.h"

#define DIODE_DIGITAL_PIN 4

using namespace std;

class UxcellPhotodiode
{
  public:
    UxcellPhotodiode()
    {
    }

    void initialize() {
		pinMode(DIODE_DIGITAL_PIN, INPUT_PULLUP);
    }
	
    uint8_t readBit()
    {
		int reading = digitalRead(DIODE_DIGITAL_PIN);
			
		if(reading == 0) {
			//light detected
			return (uint8_t) 1;
		}
		else {
			//no light detected
			return (uint8_t) 0;				
		}
	}
	
};