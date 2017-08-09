#include "UPnPResponder.h"
#include "debug.h"
#include "UPnPPacketWrapper.h"
using std::shared_ptr;
static char packetbuf_static[256];


UPnPResponder::UPnPResponder(const IPAddress &multiip, uint32_t multiport)
: multi_port(multiport),
  multi_ip(multiip),
  packet(packetbuf_static)
{
  if (udp.beginMulticast(WiFi.localIP(), multi_ip, multi_port)) {
    LOGN("beginMulticast successful");
  }
  else {
    LOGN("beginMulticast failed");
  }
}


UPnPResponder::~UPnPResponder() {
}


void UPnPResponder::addDevice (const shared_ptr<UPnPDevice> &dev) {
  devices.push_back(dev);
}


void UPnPResponder::removeDevice (int index) {
  devices.erase(devices.begin() + index);
}


void UPnPResponder::removeAllDevices() {
  devices.clear();
}


void UPnPResponder::handlePackets() {
  for(int i=0; i<devices.size(); ++i)
    devices[i]->handlePackets();

  int packetSize = udp.parsePacket();
  if (packetSize) {
    LOGN(String()
      + "\nReceived packet of size " + String(packetSize)
      + " from " + (udp.remoteIP().toString()+":"+String(udp.remotePort()))
    );
    int len = udp.read(this->packet, 255);
    if (len >= 0) this->packet[len] = 0;
    handleUDP(this->packet);
  }
}


bool UPnPResponder::handleUDP(const char *raw_packet) {
  UPnPPacketWrapper packet(raw_packet);
  if (packet.valid()) {
    for(int i=0; i<devices.size(); ++i) {
      LOGN("\nSending response to " + udp.remoteIP().toString() + ":" + String(udp.remotePort()));
      LOGN(raw_packet);
      String response = devices[i]->makeResponsePacket(packet, udp.remoteIP(), udp.remotePort());
      if (response.length() > 0) {
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.write(response.c_str());
        udp.endPacket();
      }
    }
    return true;
  }
  else {
    return false;
  }
}
