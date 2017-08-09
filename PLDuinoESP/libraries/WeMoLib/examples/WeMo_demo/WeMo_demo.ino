#include <UPnPResponder.h>
#include <WeMoSwitchEmulator.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <functional>

#define WEMO_PORT 55555
#define WEMO_NAME "Oil Lamp"

#define WIFI_SSID "YOUR SSID"
#define WIFI_KEY  "YOUR KEY"

UPnPResponder upnp(ECHO_IP, ECHO_PORT);

void setup() {
  delay(250);
  Serial.begin(115200);
  Serial.println();
  
  connectWiFi();

  upnp.addDevice(std::make_shared<WeMoSwitchEmulator>(
    WEMO_PORT,
    ESP.getChipId(),
    WEMO_NAME,
    [](bool newstate) {
      Serial.println(WEMO_NAME " turned " + String(newstate? "on" : "off"));
    }
  ));
  Serial.println("Starting fake WeMo device \"" WEMO_NAME "\" on port " + String(WEMO_PORT));
}

void loop() {
  upnp.handlePackets();
}

void connectWiFi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.softAPdisconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_KEY);
  while(WiFi.status()!=WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to " WIFI_SSID);
  Serial.println(WiFi.localIP());
}

