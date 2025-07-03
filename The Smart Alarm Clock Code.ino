/*
  Project: ESP32 Smart Room Alarm & Assistant
  Author: _shift_xd_ (Hardrik)
  Expanded with: Games & Mindfulness Modes

  Added Features:
  ✅ Red Light, Green Light Game
  ✅ Breathing Exercise (Mindfulness Mode)
  ✅ Extended Web Dashboard with Buttons
*/

#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <time.h>

#define PIR_PIN 13
#define LDR_PIN 34
#define RELAY_PIN 26
#define BUZZER_PIN 27

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
WebServer server(80);

bool gameRunning = false;
bool mindfulnessMode = false;
unsigned long gameStartTime = 0;
bool redLight = false;
bool motionDuringRed = false;

String getGameStatus() {
  if (!gameRunning) return "Game not running";
  if (redLight) return motionDuringRed ? "You moved! Game Over" : "Red Light - Don't move!";
  return "Green Light - You can move!";
}

void toggleGame() {
  gameRunning = !gameRunning;
  redLight = false;
  motionDuringRed = false;
  gameStartTime = millis();
  server.send(200, "text/plain", gameRunning ? "Game Started" : "Game Stopped");
}

void toggleMindfulness() {
  mindfulnessMode = !mindfulnessMode;
  server.send(200, "text/plain", mindfulnessMode ? "Mindfulness Started" : "Stopped");
}

void serveGameStatus() {
  server.send(200, "text/plain", getGameStatus());
}

void handleWebPage() {
  String html = "<!DOCTYPE html><html><head><title>Smart Assistant</title></head><body>";
  html += "<h1>Smart Alarm Dashboard</h1>";
  html += "<form action='/save' method='POST'><label>Alarm Time:</label><input type='time' name='alarmTime' value='07:00'>";
  html += "<button type='submit'>Set Alarm</button></form><hr>";
  html += "<h2>Games & Tools</h2>";
  html += "<button onclick=\"fetch('/startGame')\">Red Light Green Light</button><br><br>";
  html += "<button onclick=\"fetch('/mindfulness')\">Start Mindfulness Mode</button><br><br>";
  html += "<button onclick=\"fetch('/status').then(r=>r.text()).then(t=>document.getElementById('g')).then(e=>e.innerText=t)\">Check Game Status</button>";
  html += "<p id='g'>Game not running</p></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  server.on("/", handleWebPage);
  server.on("/startGame", toggleGame);
  server.on("/mindfulness", toggleMindfulness);
  server.on("/status", serveGameStatus);
  server.begin();
  Serial.println("Web Server started");
}

void loop() {
  server.handleClient();

  // Red Light Green Light game logic
  if (gameRunning) {
    if (millis() - gameStartTime > 3000) {
      redLight = !redLight;
      digitalWrite(BUZZER_PIN, redLight);
      gameStartTime = millis();
    }
    if (redLight && digitalRead(PIR_PIN)) motionDuringRed = true;
  }

  // Mindfulness mode
  if (mindfulnessMode) {
    static unsigned long breatheStart = millis();
    unsigned long t = (millis() - breatheStart) % 10000;
    if (t < 5000) {
      digitalWrite(RELAY_PIN, HIGH); // inhale
      digitalWrite(BUZZER_PIN, LOW);
    } else {
      digitalWrite(RELAY_PIN, LOW); // exhale
      digitalWrite(BUZZER_PIN, HIGH);
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
  }
}
