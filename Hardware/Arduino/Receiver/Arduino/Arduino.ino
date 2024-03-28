#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\UxcellPhotodiode.cpp"
#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\HiLetgoRGBColorSensor.cpp"

//UxcellPhotodiode
#define DIODE_DIGITAL_PIN 4
#define DIODE_ANALOG_PIN A0
#define MODE 0 //0 - digital : 1- analog

//HiLetgoRGBColorSensor
//https://github.com/adafruit/Adafruit_TCS34725/tree/master
#define INTEGRATION_TIME TCS34725_INTEGRATIONTIME_50MS
#define GAIN TCS34725_GAIN_4X

using namespace std;

//UxcellPhotodiode diode = UxcellPhotodiode(DIODE_DIGITAL_PIN, MODE);
HiLetgoRGBColorSensor colorDiode = HiLetgoRGBColorSensor(INTEGRATION_TIME, GAIN);

void setup() {
  Serial.begin(9600);
  //diode.initialize();
  if (!colorDiode.initialize()) {
    Serial.println("No TCS34725 found ... check your connections");
  }
}

void loop() {
  Serial.println(diode.read());
}
