#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
const char* WIFI_SSID = "NAMA WIFI KAMU";
const char* WIFI_PASSWORD = "PASSWORD WIFI KAMU";


const char* BOT_TOKEN = "BOT TOKEN TELEGRAM KAMU";
String chatId = "ID TELEGRAM KAMU";


WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

const int relay1 = 25;  // Pin yang digunakan untuk mengendalikan lampu
const int relay2 = 26;  // Pin yang digunakan untuk mengendalikan Kipas


void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  // Menghubungkan ke WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
  }
  Serial.println("Connected to WiFi");

  // Menginisialisasi pin untuk lampu dan kipas

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  // Memulai koneksi ke Telegram
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Ini opsional, bergantung pada versi pustaka yang digunakan
}

void loop() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  for (int i = 0; i < numNewMessages; i++) {
    chatId = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    Serial.println(text);

    if (text == "say") {
      bot.sendMessage(chatId, "Apa Kabar!");
      delay(100);
      bot.sendMessage(chatId, "Apa yang bisa dibantu!");
    }

    else if (text == "hidupkan lampu 1") {
      digitalWrite(relay1, HIGH);
      bot.sendMessage(chatId, "Lampu 1 telah dihidupkan!");
    }

    else if (text == "matikan lampu 1") {
      digitalWrite(relay1, LOW);
      bot.sendMessage(chatId, "Lampu 1 telah dimatikan!");
    }

    else if (text == "hidupkan lampu 2") {
      digitalWrite(relay2, HIGH);
      bot.sendMessage(chatId, "Lampu 2 telah dihidupkan!");
    }

    else if (text == "matikan lampu 2") {
      digitalWrite(relay2, LOW);
      bot.sendMessage(chatId, "Lampu 2 telah dimatikan!");
    }

    else if (text == "hidupkan semua") {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      bot.sendMessage(chatId, "Semua lampu telah dihidupkan!");
    }

    else if (text == "matikan semua") {
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      bot.sendMessage(chatId, "Semua lampu telah dimatikan!");
    }

    // 🔍 STATUS LAMPU
    else if (text == "status") {
      String statusLampu1 = (digitalRead(relay1) == HIGH) ? "HIDUP" : "MATI";
      String statusLampu2 = (digitalRead(relay2) == HIGH) ? "HIDUP" : "MATI";

      String pesan = "Status Lampu:\n";
      pesan += "💡 Lampu 1: " + statusLampu1 + "\n";
      pesan += "💡 Lampu 2: " + statusLampu2;

      bot.sendMessage(chatId, pesan);
    }
  }

  delay(1000);
}
