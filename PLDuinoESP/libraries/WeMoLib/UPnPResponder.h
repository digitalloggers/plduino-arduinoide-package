#pragma once
#include <Arduino.h>
#include "UPnPDevice.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include <vector>
#include <memory>

#define ECHO_IP     IPAddress(239,255,255,250)
#define ECHO_PORT   1900

class UPnPResponder {
public:
  UPnPResponder(const IPAddress &ipmulti, uint32_t port);
  virtual ~UPnPResponder();
  void addDevice(const std::shared_ptr<UPnPDevice> &device);
  const std::vector<std::shared_ptr<UPnPDevice>> &getDevices() const { return devices; }
  void removeDevice (int index);
  void removeAllDevices();
  void handlePackets();
private:
  bool handleUDP(const char *raw_packet);
  std::vector<std::shared_ptr<UPnPDevice>> devices;
  WiFiUDP udp;
  uint32_t multi_port;
  IPAddress multi_ip;
private:
  char *packet;
};
