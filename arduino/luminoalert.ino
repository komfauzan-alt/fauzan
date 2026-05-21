#define BUZZER 2

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);                    // INPUT DARI SENSOR CAHAYA (LDR)
  pinMode(LED_BUILTIN, OUTPUT);          // OUTPUT LED PIN 13
  pinMode(BUZZER, OUTPUT);               // OUTPUT BUZZER PIN 2
}

// LED berkedip
void ledBlink(int speed) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(speed);
  digitalWrite(LED_BUILTIN, LOW);
}

// SUARA "TINUNG" CEPAT & PENDEK (dipercepat)
void soundAlert(int speed) {
  tone(BUZZER, 1200);    // nada dinaikkan sedikit untuk kesan lebih tegas
  delay(18);             // durasi bunyi dipersingkat (18 ms)
  noTone(BUZZER);
  delay(50);             // jeda antar bunyi lebih cepat (50 ms)
}

void loop() {
  int sensor_value = analogRead(A5);
  if(sensor_value < 100) {
    ledBlink(100);       // LED juga dipercepat agar sinkron
    soundAlert(100);     // tetap panggil fungsi dengan parameter
  } else {
    noTone(BUZZER);
  }
}
