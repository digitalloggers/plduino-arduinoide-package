#pragma once

/*
 *  Usage:
 *    void setup() {
 *      ...
 *      setupWiFi();
 *      SPIFFS.begin();
 *      ...
 *      ESP8266WebFileManager::begin(9999);
 *    }
 *    void loop() {
 *      ESP8266WebFileManager::handleClient();
 *    }
 *
 */

namespace ESP8266WebFileManager {
  void begin(int port);
  void end();
  bool handleClient();
}
