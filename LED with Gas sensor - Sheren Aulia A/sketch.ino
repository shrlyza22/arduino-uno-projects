const int gasPin = A0;     // Sensor gas (analog)
const int ledPin = 8;      // LED

const int threshold = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);    
}

void loop() {
  int gasValue = analogRead(gasPin);

  Serial.print("Nilai Gas: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    digitalWrite(ledPin, HIGH);   // Gas terdeteksi
  } else {
    digitalWrite(ledPin, LOW);    // Kondisi tidak terdeteksi gas 
  }

  delay(500);
}
