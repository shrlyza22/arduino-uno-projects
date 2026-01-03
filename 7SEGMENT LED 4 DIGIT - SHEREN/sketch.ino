const int segA = 2;
const int segB = 3;
const int segC = 4;
const int segD = 5;
const int segE = 6;
const int segF = 7;
const int segG = 8;

const int D1 = 10;
const int D2 = 11;
const int D3 = 12;
const int D4 = 13;

void setup(){
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);  
}

void loop(){
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  S();
  delay(1000);
  H();
  delay(1000);
  E_();
  delay(1000);
  R();
  delay(1000);
  E_();
  delay(1000);
  N();
  delay(1000);
}

void S(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void H(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void E_(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void R(){
  digitalWrite(segA, LOW);   
  digitalWrite(segB, HIGH);  
  digitalWrite(segC, HIGH);  
  digitalWrite(segD, HIGH);  
  digitalWrite(segE, LOW);   
  digitalWrite(segF, LOW);  
  digitalWrite(segG, HIGH);  
}

void N(){
  digitalWrite(segA, LOW);  
  digitalWrite(segB, LOW);  
  digitalWrite(segC, LOW);  
  digitalWrite(segD, HIGH); 
  digitalWrite(segE, LOW);   
  digitalWrite(segF, LOW);   
  digitalWrite(segG, HIGH);  
}
