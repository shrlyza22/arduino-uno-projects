#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// --- KONFIGURASI PIN RFID (SPI KHUSUS MEGA) ---
#define SS_PIN  53  
#define RST_PIN 9   
MFRC522 mfrc522(SS_PIN, RST_PIN);

// --- KONFIGURASI PIN SENSOR & AKTUATOR ---
#define TRIG_PIN 7      
#define ECHO_PIN 8       
#define GATE_SERVO_PIN 6 
#define DOOR_SERVO_PIN 11 

// LED Indikator
#define LED_GREEN A6    
#define LED_RED   A7    

// --- KONFIGURASI KEYPAD 4x4 ---
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; 
byte colPins[COLS] = {A0, A1, A2, A3}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// --- KONFIGURASI LCD I2C ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo gateServo;
Servo doorServo;

// --- DATA AKSES ---
String correctPIN = "1234"; 
String inputPIN = "";
String validUID = "AA BB CC DD"; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  lcd.init();
  lcd.backlight();
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  gateServo.attach(GATE_SERVO_PIN);
  doorServo.attach(DOOR_SERVO_PIN);
  
  gateServo.write(0); 
  doorServo.write(0); 
  
  displayDoorStandby();
  Serial.println("Sistem Siap...");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    checkGate();
  }

  char key = keypad.getKey();
  if (key) {
    handleDoor(key);
  }
}

// === FUNGSI KONTROL GERBANG ===
void checkGate() {
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  Serial.println("====================");
  Serial.println("Kartu Terdeteksi");
  Serial.print("UID Kartu: ");
  Serial.println(content.substring(1));

  if (content.substring(1) == validUID) {
    Serial.println("Access Granted.");
    Serial.println("Gerbang Sedang Dibuka...");
    digitalWrite(LED_GREEN, HIGH);
    gateServo.write(90); 
    delay(3000);

    Serial.println("Menunggu kendaraan melewati gerbang...");

    while(getDistance() < 20) { 
      delay(500); 
    }
    delay(1000);
    gateServo.write(0); 
    digitalWrite(LED_GREEN, LOW);
    Serial.println("Gerbang Sedang Ditutup...");
    Serial.println("Gerbang Tertutup");
  } else {
    Serial.println("Access Denied! Kartu Tidak Dikenal.");
    digitalWrite(LED_RED, HIGH);
    delay(1000);
    digitalWrite(LED_RED, LOW);
  }
  mfrc522.PICC_HaltA();
}

void handleDoor(char key) {
  if (key == '#') { 
    if (inputPIN == correctPIN) {
      Serial.println("PIN Benar!");
      Serial.println("Membuka pintu...");

      lcd.clear();
      lcd.print("PIN Benar!");
      
      digitalWrite(LED_GREEN, HIGH);
      doorServo.write(90); // Servo posisi buka
      delay(2000); // Jeda agar user punya waktu melihat LCD

      lcd.clear();
      lcd.print("Pintu Terbuka");

      // AUTO LOCK BERDASARKAN TIMER
      unsigned long timeoutStart = millis();
      
      while(millis() - timeoutStart < 10000) {
        int sisaWaktu = 10 - ((millis() - timeoutStart) / 1000);
        lcd.setCursor(0, 1);
        lcd.print("Lock dlm: ");
        lcd.print(sisaWaktu);
        lcd.print("s ");
        
        delay(100);
      }
      
      lcd.clear();
      lcd.print("Auto Locking...");
      
      Serial.println("Pintu dikunci kembali");
      doorServo.write(0);
      digitalWrite(LED_GREEN, LOW);
      
      delay(2000);
      displayDoorStandby();

    } else {
      lcd.clear();
      lcd.print("PIN SALAH!");
      digitalWrite(LED_RED, HIGH);
      delay(2000);
      digitalWrite(LED_RED, LOW);
      displayDoorStandby();
    }
    inputPIN = ""; 
  } 
  else if (key == '*') { 
    inputPIN = "";
    displayDoorStandby();
  } 
  else { 
    // Batasi input agar tidak lebih dari 16 karakter (biar LCD gak berantakan)
    if (inputPIN.length() < 16) {
      inputPIN += key;
      lcd.setCursor(0, 1);
      lcd.print("PIN: ");
      for(int i=0; i<inputPIN.length(); i++) {
        lcd.print("*"); 
      }
    }
  }
}

void displayDoorStandby() {
  lcd.clear();
  lcd.print("Pintu Rumah");
  lcd.setCursor(0, 1);
  lcd.print("Input PIN:");
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}