#include <FS.h>

void setup() {
  delay(300);
  Serial.begin(115200);
  Serial.println();
  
  Serial.println("SPIFFS formatting will begin in 10 seconds...");
  delay(10000);
  Serial.print("Formatting SPIFFS... ");
  SPIFFS.format();
  Serial.println("done.");
}

void loop() {
}

