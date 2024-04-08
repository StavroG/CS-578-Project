#define baudrate 9600
#define delayMs 1000
#define led_pin 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baudrate);

  Serial.println("Transmitter Started");

  pinMode(led_pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_pin, HIGH);

  delay(delayMs);

  digitalWrite(led_pin, LOW);

  delay(delayMs);
}
