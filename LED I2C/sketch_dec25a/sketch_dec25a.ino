#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String textAtas = "AKU KANGEEN";
String textBawah = "SAMA KALIANN!!";

void setup() {
  lcd.init();
  lcd.backlight();

  int startAtas  = (16 - textAtas.length()) / 2;
  int startBawah = (16 - textBawah.length()) / 2;

  // Animasi ATAS dari kiri
  for (int i = -textAtas.length(); i <= startAtas; i++) {
    lcd.clear();
    if (i >= 0) {
      lcd.setCursor(i, 0);
      lcd.print(textAtas);
    }
    delay(200);
  }

  // Animasi BAWAH dari kanan
  for (int i = 16; i >= startBawah; i--) {
    lcd.clear();
    lcd.setCursor(i, 1);
    lcd.print(textBawah);
    delay(200);
  }

  // FINAL TENGAH (GAK ILANG)
  lcd.clear();
  lcd.setCursor(startAtas, 0);
  lcd.print(textAtas);

  lcd.setCursor(startBawah, 1);
  lcd.print(textBawah);
}

void loop() {
  // kosong. damai. selesai.
}
