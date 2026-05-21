#include <Wire.h>                      // Untuk komunikasi I2C ke OLED
#include <Adafruit_GFX.h>             // Library grafis dari Adafruit
#include <Adafruit_SSD1306.h>         // Library khusus untuk OLED SSD1306

// Ukuran layar OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1              // Gak dipakai, jadi diset -1

// Bikin objek display untuk OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Posisi awal dan ukuran mata
int leftEyeX = 40;       // Posisi X mata kiri
int rightEyeX = 80;      // Posisi X mata kanan
int eyeY = 18;           // Posisi Y mata (semua mata)
int eyeWidth = 25;       // Lebar mata
int eyeHeight = 30;      // Tinggi mata

// Target posisi mata (biar geraknya halus)
int targetLeftEyeX = leftEyeX;
int targetRightEyeX = rightEyeX;
int moveSpeed = 2;       // Kecepatan gerak mata

// Variabel buat kedip
int blinkState = 0;              // 0 = mata buka, 1 = mata kedip
int blinkDelay = 2000;           // Waktu antar kedipan (2 detik)
unsigned long lastBlinkTime = 0; // Waktu terakhir kedip
unsigned long moveTime = 0;      // Waktu terakhir gerak mata

// Ekspresi wajah: 0 = normal, 1 = senang, 2 = sedih, 3 = marah
int expression = 0;

void setup() {
  // Mulai layar OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Alamat default OLED: 0x3C
  display.display();  // Nyalain layar
  delay(2000);        // Tunggu 2 detik
}

void loop() {
  unsigned long currentTime = millis();  // Waktu sekarang (dalam milidetik)

  // === Logika Kedip ===
  if (currentTime - lastBlinkTime > blinkDelay && blinkState == 0) {
    blinkState = 1;               // Mulai kedip
    lastBlinkTime = currentTime;
  } 
  else if (currentTime - lastBlinkTime > 400 && blinkState == 1) {
    blinkState = 0;               // Selesai kedip
    lastBlinkTime = currentTime;
  }

  // === Gerak Mata Random ===
  if (currentTime - moveTime > random(2000, 5000) && blinkState == 0) {
    int eyeMovement = random(0, 3);  // 0 = tengah, 1 = dekat, 2 = jauh
    if (eyeMovement == 1) {
      targetLeftEyeX = 30;
      targetRightEyeX = 60;
    } else if (eyeMovement == 2) {
      targetLeftEyeX = 50;
      targetRightEyeX = 80;
    } else {
      targetLeftEyeX = 40;
      targetRightEyeX = 70;
    }
    moveTime = currentTime;
  }

  // === Gerakin mata pelan-pelan ke posisi target ===
  if (leftEyeX != targetLeftEyeX) {
    leftEyeX += (targetLeftEyeX - leftEyeX) / moveSpeed;
  }
  if (rightEyeX != targetRightEyeX) {
    rightEyeX += (targetRightEyeX - rightEyeX) / moveSpeed;
  }

  // Bersihin layar sebelum gambar ulang
  display.clearDisplay();

  // === Gambar Mata Kiri ===
  if (blinkState == 0) {
    drawExpression(leftEyeX, eyeY, eyeWidth, eyeHeight, expression);  // Mata terbuka
  } else {
    display.fillRect(leftEyeX, eyeY + eyeHeight / 2 - 2, eyeWidth, 4, WHITE); // Mata kedip
  }

  // === Gambar Mata Kanan ===
  if (blinkState == 0) {
    drawExpression(rightEyeX, eyeY, eyeWidth, eyeHeight, expression);  // Mata terbuka
  } else {
    display.fillRect(rightEyeX, eyeY + eyeHeight / 2 - 2, eyeWidth, 4, WHITE); // Mata kedip
  }

  // Tampilkan hasil di layar
  display.display();

  delay(50); // Kasih jeda biar gak terlalu flicker

  // === Ganti ekspresi tiap beberapa detik ===
  if (currentTime - moveTime > random(3000, 7000)) {
    expression = random(0, 4);  // 0 s.d. 3 (acak)
    moveTime = currentTime;
  }
}

// Fungsi untuk gambar ekspresi wajah di mata
void drawExpression(int eyeX, int eyeY, int eyeWidth, int eyeHeight, int exp) {
  // Gambar bentuk dasar mata (kotak bulat)
  display.fillRoundRect(eyeX, eyeY, eyeWidth, eyeHeight, 5, WHITE);

  // Tambah ekspresi di dalam mata
  switch (exp) {
    case 0: // Normal (gak ada tambahan)
      break;

    case 1: // Senang
      display.fillRect(eyeX + 5, eyeY + 18, eyeWidth - 10, 4, WHITE);
      break;

    case 2: // Sedih
      display.fillRect(eyeX + 5, eyeY + eyeHeight - 12, eyeWidth - 10, 4, WHITE);
      break;

    case 3: // Marah
      display.fillRect(eyeX + 5, eyeY + 7, eyeWidth - 10, 4, WHITE);
      break;
  }
}
