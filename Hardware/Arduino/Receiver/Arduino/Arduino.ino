#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\UxcellPhotodiode.cpp"

#define DIODE_DIGITAL_PIN 4
#define DIODE_ANALOG_PIN A0
#define MODE 0 //0 - digital : 1- analog

using namespace std;

UxcellPhotodiode diode = UxcellPhotodiode(DIODE_DIGITAL_PIN, MODE);

void setup() {
  Serial.begin(9600);
  diode.initialize();
}

void loop() {
  Serial.println(diode.read());
}
