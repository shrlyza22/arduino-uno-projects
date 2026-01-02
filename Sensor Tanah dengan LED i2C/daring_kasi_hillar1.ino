// C++ code
//
const int soilPin = A0;
const int ledPin = 8;
int threshold = 450;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int soilValue = analogRead(soilPin);
  Serial.println(soilValue);

  if (soilValue <= threshold) {
    digitalWrite(ledPin, HIGH); // Tanah kering
    Serial.println("Tanah Kering");
  } else {
    digitalWrite(ledPin, LOW);  // Tanah basah
    Serial.println("Tanah Basah");
  }

  delay(1000);
}
