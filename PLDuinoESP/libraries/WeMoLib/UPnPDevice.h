#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "UPnPPacketWrapper.h"


class UPnPDevice {
public:
  virtual const String &getPersistentUUID() const = 0;
  virtual uint32_t getPort() const = 0;
  virtual const IPAddress &getIP() const = 0;
  virtual void handlePackets() = 0;
  virtual String makeResponsePacket(
    const UPnPPacketWrapper &packet,
    const IPAddress &remote_ip,
    uint32_t remote_port
  );
};
