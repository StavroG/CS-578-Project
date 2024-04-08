#define buadrate 9600
#define delayMs 1000
#define analog_pin A1
#define digital_pin 2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(buadrate);

  pinMode(digital_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor_value = analogRead(analog_pin);
  bool a = digitalRead(digital_pin);
  Serial.println(sensor_value);
  Serial.println(a);
  delay(delayMs);
}
