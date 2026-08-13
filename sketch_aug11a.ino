#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Struct untuk timing yang presisi
struct LyricPair {
  const char* line1;
  const char* line2;
  int charDelay;    // delay per karakter (ms)
  int pauseAfter;   // jeda setelah baris selesai (ms)
};

// Lirik dengan timing berdasarkan detik 0:58 - 1:06
const LyricPair lyrics[] = {
  // 0:58 - Mulai
  {"I wonder where", "I'm at", 70, 400},      // ~1.5 detik
  {"Oh, she a ten", "out of ten (oh)", 65, 300}, // ~1.5 detik
  {"Look good from", "the front and", 60, 200},   // ~1.2 detik
  {"back", "I don't know,", 55, 300},          // ~0.8 detik
  {"shawty, do you", "love me like you", 50, 300}, // ~1.2 detik
  {"say? (Like you", "say)", 45, 400},         // ~1.0 detik 
  {"Tell me, do you", "love me like you", 50, 300}, // ~1.2 detik
  {"claimm? (Claimmm)", "", 50, 700},             // ~0.8 detik
  {"@miragee", "", 50, 700},
};

int lyricCount = sizeof(lyrics) / sizeof(lyrics[0]);

void typeWriter(const char* text, int row, int charDelay) {
  lcd.setCursor(0, row);
  for (int i = 0; text[i] != '\0'; i++) {
    lcd.print(text[i]);
    delay(charDelay);
  }
}

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  for (int i = 0; i < lyricCount; i++) {
    lcd.clear();
    
    if (strlen(lyrics[i].line1) > 0) {
      typeWriter(lyrics[i].line1, 0, lyrics[i].charDelay);
    }
    
    if (strlen(lyrics[i].line2) > 0) {
      typeWriter(lyrics[i].line2, 1, lyrics[i].charDelay);
    }
    
    delay(lyrics[i].pauseAfter);
  }
  
  // ===== TAMBAHAN: Jeda 5 detik SEBELUM LOOP LAGI =====
  delay(5000); // 5 detik jeda sebelum kembali ke lirik awal
  
  // Opsional: Tampilkan pesan "RECORDING" atau kosongkan layar
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Ready to record");
  // delay(2000);
  // lcd.clear();
  // delay(3000);
}