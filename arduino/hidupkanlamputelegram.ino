#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

const char* WIFI_SSID = "NAMA WIFI KAMU";
const char* WIFI_PASSWORD = "PASSWORD WIFI";

const char* BOT_TOKEN = "MASUKAN BOT TOKEN";
String chatId = "MASUKAN CHAT ID";

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

const int relay1 = 25;
const int relay2 = 26;

void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  // Relay OFF saat awal
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  // Koneksi WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() {

  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  for (int i = 0; i < numNewMessages; i++) {

    chatId = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    Serial.println(text);

    // =========================
    // SAPA
    // =========================
    if (text == "say") {

      bot.sendMessage(chatId, "Apa Kabar!");
      delay(100);
      bot.sendMessage(chatId, "Apa yang bisa dibantu!");
    }

    // =========================
    // MENUNJUKAN LIST
    // =========================
    else if (text == "list") {

      String pesan = "Daftar Perintah:\n\n";
      pesan += "hidupkan lampu 1\n";
      pesan += "matikan lampu 1\n";
      pesan += "hidupkan lampu 2\n";
      pesan += "matikan lampu 2\n";
      pesan += "hidupkan semua\n";
      pesan += "matikan semua\n";

  bot.sendMessage(chatId, pesan);
}

    // =========================
    // LAMPU 1
    // =========================
    else if (text == "hidupkan lampu 1") {

      digitalWrite(relay1, LOW); // ON
      bot.sendMessage(chatId, "Lampu 1 telah dihidupkan!");
    }

    else if (text == "matikan lampu 1") {

      digitalWrite(relay1, HIGH); // OFF
      bot.sendMessage(chatId, "Lampu 1 telah dimatikan!");
    }

    // =========================
    // LAMPU 2
    // =========================
    else if (text == "hidupkan lampu 2") {

      digitalWrite(relay2, LOW); // ON
      bot.sendMessage(chatId, "Lampu 2 telah dihidupkan!");
    }

    else if (text == "matikan lampu 2") {

      digitalWrite(relay2, HIGH); // OFF
      bot.sendMessage(chatId, "Lampu 2 telah dimatikan!");
    }

    // =========================
    // SEMUA
    // =========================
    else if (text == "hidupkan semua") {

      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);

      bot.sendMessage(chatId, "Semua lampu telah dihidupkan!");
    }

    else if (text == "matikan semua") {

      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);

      bot.sendMessage(chatId, "Semua lampu telah dimatikan!");
    }

    // =========================
    // STATUS
    // =========================
    else if (text == "status") {

      String statusLampu1 =
        (digitalRead(relay1) == LOW) ? "HIDUP" : "MATI";

      String statusLampu2 =
        (digitalRead(relay2) == LOW) ? "HIDUP" : "MATI";

      String pesan = "Status Lampu:\n";
      pesan += "💡 Lampu 1: " + statusLampu1 + "\n";
      pesan += "💡 Lampu 2: " + statusLampu2;

      bot.sendMessage(chatId, pesan);
    }
  }

  delay(1000);
}