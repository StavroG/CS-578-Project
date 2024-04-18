#include "C:\Users\Ipacheco\source\repos\CS-578-Project\Hardware\Arduino\LiFi.cpp"

using namespace std;

LiFi lifi = LiFi();

void setup() {
  Serial.begin(9600);
  lifi.initializeTransmitter();
}

void loop() {
  lifi.transmitLoop();
}
