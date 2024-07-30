#define BLYNK_TEMPLATE_ID "TMPL6wM5h41Gz"
#define BLYNK_TEMPLATE_NAME "PC switch"
#define BLYNK_AUTH_TOKEN "4SKw8XGl3LnE2GTUJd6akBHaiUOoFzIB"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Ticker.h>

char ssid[] = "SUST WiFi";
char password[] = "SUST10s10";
char auth[] = BLYNK_AUTH_TOKEN;

#define RELAY_PIN 26 // Use GPIO 26 for ESP32

Ticker restartTicker;
unsigned long lastWiFiCheck = 0;
const unsigned long wifiCheckInterval = 30000; // 30 seconds
const unsigned long wifiReconnectTimeout = 60000; // 1 minute
const int maxReconnectAttempts = 10; // Max attempts before forcing restart
int reconnectAttempts = 0;
bool shouldRestart = false;

void forceRestart() {
  ESP.restart();
}

void restartMCU() {
  shouldRestart = true;
  delay(100); // Allow some time for messages to be sent
  ESP.restart();
}

void checkWiFiAndReconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();

    // Wait for connection with timeout
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < wifiReconnectTimeout) {
      delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
      reconnectAttempts = 0; // Reset the counter on successful reconnection
    } else {
      reconnectAttempts++;
      if (reconnectAttempts >= maxReconnectAttempts) {
        forceRestart();
      }
    }
  }
}

void checkBlynkConnection() {
  if (!Blynk.connected()) {
    Blynk.connect();
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Ensure relay is off
  
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Connect to Blynk
  Blynk.begin(auth, ssid, password);

  // Set up the periodic restart every 6 hours
  restartTicker.attach(21600, restartMCU); // 21600 seconds = 6 hours
}

void loop() {
  Blynk.run();

  unsigned long currentMillis = millis();

  // Check WiFi connection every 30 seconds
  if (currentMillis - lastWiFiCheck >= wifiCheckInterval) {
    lastWiFiCheck = currentMillis;
    checkWiFiAndReconnect();
  }

  // If restart flag is set, force restart
  if (shouldRestart) {
    forceRestart();
  }

  // Ensure WiFi is connected
  if (WiFi.status() != WL_CONNECTED) {
    checkWiFiAndReconnect();
  }

  // Check Blynk connection
  checkBlynkConnection();
}

BLYNK_WRITE(V0) {
  int relayState = param.asInt();
  relayState ? digitalWrite(RELAY_PIN, LOW) : digitalWrite(RELAY_PIN, HIGH);
}
