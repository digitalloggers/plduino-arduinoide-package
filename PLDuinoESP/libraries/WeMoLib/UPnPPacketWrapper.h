#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <functional>

class UPnPPacketWrapper {
public:
  UPnPPacketWrapper (const char *raw_packet) : raw_buf(raw_packet) {}
  bool valid() const { return isMSEARCH(); }
  bool isMSEARCH() const { return strstr(raw_buf, "M-SEARCH"); }
  const char *raw() const { return raw_buf; }
private:
  const char *raw_buf;
};
