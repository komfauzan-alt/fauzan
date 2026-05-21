#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const char* ssid = "indihome";
const char* password = "15042009";

const int espLed = 2;
const int ledPin1 = 4;  // Dapur
const int ledPin2 = 5;  // Tamu
const int ledPin3 = 19; // Makan
const int ledPin4 = 22; // Toilet

bool dapurLedState = false;
bool tamuLedState = false;
bool makanLedState = false;
bool toiletLedState = false;

void setup() {
  Serial.begin(115200);

  pinMode(espLed, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  WiFi.begin(ssid, password);
  Serial.print("connecting to wifi indihome...");

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(espLed, LOW);
    delay(1000);
    Serial.print(".");
  }

  digitalWrite(espLed, HIGH);
  Serial.println("");
  Serial.println("connected to wifi network!: ");
  Serial.println(WiFi.localIP());

  // Routes LED individual
  server.on("/dapur", HTTP_GET, getDapurLed);
  server.on("/tamu", HTTP_GET, getTamuLed);
  server.on("/makan", HTTP_GET, getMakanLed);
  server.on("/toilet", HTTP_GET, getToiletLed);

  server.on("/dapur", HTTP_POST, setDapurLed);
  server.on("/tamu", HTTP_POST, setTamuLed);
  server.on("/makan", HTTP_POST, setMakanLed);
  server.on("/toilet", HTTP_POST, setToiletLed);

  // Routes ALL ON / OFF
  server.on("/allon", HTTP_POST, setAllLedOn);
  server.on("/alloff", HTTP_POST, setAllLedOff);

  server.begin();
  Serial.println("Server started...");
}

void loop() {
  server.handleClient();
}

// ======== Individual set methods ========
void setDapurLed() {
  dapurLedState = !dapurLedState;
  digitalWrite(ledPin1, dapurLedState ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", dapurLedState ? "ON" : "OFF");
}

void setTamuLed() {
  tamuLedState = !tamuLedState;
  digitalWrite(ledPin2, tamuLedState ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", tamuLedState ? "ON" : "OFF");
}

void setMakanLed() {
  makanLedState = !makanLedState;
  digitalWrite(ledPin3, makanLedState ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", makanLedState ? "ON" : "OFF");
}

void setToiletLed() {
  toiletLedState = !toiletLedState;
  digitalWrite(ledPin4, toiletLedState ? HIGH : LOW);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", toiletLedState ? "ON" : "OFF");
}

// ======== Individual get methods ========
void getDapurLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", dapurLedState ? "ON" : "OFF");
}

void getTamuLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", tamuLedState ? "ON" : "OFF");
}

void getMakanLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", makanLedState ? "ON" : "OFF");
}

void getToiletLed() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", toiletLedState ? "ON" : "OFF");
}

// ======== All LEDs ON ========
void setAllLedOn() {
  dapurLedState = true;
  tamuLedState = true;
  makanLedState = true;
  toiletLedState = true;

  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ALL ON");
}

// ======== All LEDs OFF ========
void setAllLedOff() {
  dapurLedState = false;
  tamuLedState = false;
  makanLedState = false;
  toiletLedState = false;

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "ALL OFF");
}
