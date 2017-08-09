#include <ESP8266WebFileManager.h>
#include <ESP8266WiFi.h>
#include <FS.h>

void setupWiFi() {
  WiFi.disconnect();
  WiFi.softAP("ESP8266WebFileManagerSSID", "password");
  Serial.println(WiFi.softAPIP());
  Serial.println(WiFi.localIP());
}

void setup() {
  delay(300);
  Serial.begin(115200);
  Serial.println();

  setupWiFi();
  SPIFFS.begin();
  ESP8266WebFileManager::begin(80);
}

void loop() {
  ESP8266WebFileManager::handleClient();
}

