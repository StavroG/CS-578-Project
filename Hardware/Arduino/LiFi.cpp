#include "Arduino.h"
#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\Transmitter\NeoPixelJewel.cpp"
#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\Receiver\UxcellPhotodiode.cpp"
#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\Receiver\HiLetgoRGBColorSensor.cpp"

#define DELAYMS 30

using namespace std;

class LiFi
{
  private:
  	uint8_t current_bit;
	uint8_t previous_bit;
	NeoPixelJewel* led;
	UxcellPhotodiode* diode;
	HiLetgoRGBColorSensor *colorDiode;	
	
	void sendByte() {
		
		if(Serial.available() < 1){
			return;
		}			
		
		uint8_t currentByte = Serial.read();
		led->turnOff();
			
		for (int j = 0; j < 8; j++) {
			
			bool isBitSet = bitRead(currentByte, j);
			  
			if(isBitSet) {
				led->turnOn();
			}
			else {
				led->turnOff();
			}
			
		}
		
		led->turnOn();
		delay(100);
	}
	
	void readByte() {
		
		uint8_t reading = 0;
		delay(DELAYMS * 1.5);
		
		for (int i = 0; i < 8; i++) {
			
			uint8_t newestBit = diode->readBit(); // get latest bit		
		
			if(newestBit == 0) {
				bitClear(reading, i);
			}
			else {
				bitSet(reading, i);
			}
			
			delay(DELAYMS);
			
		}
		
		char buffer[2];
		sprintf(buffer, "%c", reading);
		Serial.print(buffer);
		
	}
	
  public:
  
    LiFi()
    {
		
    }
	
	void initializeTransmitter() {
		led = &NeoPixelJewel();
		led->initialize();
	}
	
	void initializeReciever() {
		diode = &UxcellPhotodiode();
		diode->initialize();
	}
	
	void initializeRGBReciever() {
		colorDiode = &HiLetgoRGBColorSensor();
		colorDiode->initialize();
	}
	
	void transmitLoop() {
		sendByte();
	}
	
	void recieveLoop() {
		current_bit = diode->readBit();
		if(!current_bit && previous_bit) {
			readByte();
		}
		
		previous_bit = current_bit;
	}
	
};