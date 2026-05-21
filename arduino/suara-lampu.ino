//Rangkaian Pengontrol Lampu dengan Sensor Suara
//Follow My Instagram hanif.jez

boolean lampON = false;
int inSensor = A0;
int lamp = 9;

void setup() {
  Serial.begin(9600);
  pinMode(inSensor, INPUT);
  pinMode(lamp, OUTPUT);
  digitalWrite(lamp, LOW);
}

void loop() {
  if (digitalRead(inSensor) == 0) {
    if (lampON == false) {
      digitalWrite(lamp, HIGH);
      lampON = true;
      Serial.println("Lampu Nyala");
      delay(1000);
    } else {
      digitalWrite(lamp, LOW);
      lampON = false;
      Serial.println("Lampu Mati");
      delay(1000);
    }
  }
}
