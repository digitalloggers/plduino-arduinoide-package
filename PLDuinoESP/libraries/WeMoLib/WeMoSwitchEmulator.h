#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <functional>
#include "UPnPDevice.h"
#include "UPnPPacketWrapper.h"


// This class emulates WeMo Socket device.
// WeMo(R) is a registered trademark of Belkin International, Inc.
class WeMoSwitchEmulator : public UPnPDevice {
public:
  typedef std::function<void(bool new_state)> SwitchOnHandler;
  WeMoSwitchEmulator(
    uint32_t port,
    uint32_t chipid,
    const String &alexa_name,
    const SwitchOnHandler &turn_on_handler
  );
  inline virtual uint32_t getPort() const override { return port; }
  inline virtual const IPAddress &getIP() const override { return WiFi.localIP(); }
  inline virtual const String &getPersistentUUID() const override { return persistent_uuid; }
  virtual void handlePackets();
  virtual String makeResponsePacket(
    const UPnPPacketWrapper &packet,
    const IPAddress &remote_ip,
    uint32_t remote_port
  );
private:
  virtual void prepareIds(uint32_t chipId);
private:
  SwitchOnHandler switchOn;
  ESP8266WebServer http;
  uint32_t chip_id;
  String persistent_uuid;
  String serial;
  String device_name;
  uint32_t port;
};
