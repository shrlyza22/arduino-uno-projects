void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);        
  pinMode(2, INPUT_PULLUP);   
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == LOW) {  
    digitalWrite(8, LOW);      
  } else {
    digitalWrite(8, HIGH);      
  }
}
