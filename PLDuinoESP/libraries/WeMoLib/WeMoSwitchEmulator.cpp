#include "WeMoSwitchEmulator.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "debug.h"


void WeMoSwitchEmulator::prepareIds(uint32_t chipId) {
  char uuid[64];
  sprintf_P(uuid,
    PSTR("38323636-4558-4dda-9188-cda0e6" "%02x" "%02x" "%02x"),
    (uint16_t)((chipId >> 16) & 0xff),
    (uint16_t)((chipId >>  8) & 0xff),
    (uint16_t)( chipId        & 0xff)
  );
  chip_id = chipId;
  serial = String(uuid);
  persistent_uuid = "Socket-1_0-" + serial;
}


String WeMoSwitchEmulator::makeResponsePacket(
  const UPnPPacketWrapper &packet,
  const IPAddress &remote_ip, uint32_t remote_port
) {
  return (
    strstr(packet.raw(), "urn:Belkin:device:**")==NULL?
        String("")
      : String(
          "HTTP/1.1 200 OK\r\n"
          "CACHE-CONTROL: max-age=86400\r\n"
          "DATE: Fri, 15 Apr 2016 04:56:29 GMT\r\n"
          "EXT:\r\n"
          "LOCATION: http://" + IPAddress(getIP()).toString() + ":" + String(getPort()) + "/setup.xml\r\n"
          "OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n"
          "01-NLS: b9200ebb-736d-4b93-bf03-835149d13983\r\n"
          "SERVER: Unspecified, UPnP/1.0, Unspecified\r\n"
          "ST: urn:Belkin:device:**\r\n"
          "USN: uuid:" + getPersistentUUID() + "::urn:Belkin:device:**\r\n"
          "X-User-Agent: redsonic\r\n"
          "\r\n"
        )
  );
}


WeMoSwitchEmulator::WeMoSwitchEmulator(
  uint32_t port_,
  uint32_t chipid,
  const String &alexa_name,
  const SwitchOnHandler &switch_on_handler
)
: http(port_),
  port(port_),
  device_name(alexa_name),
  switchOn(switch_on_handler)
{
  prepareIds(chipid);

  http.on("/upnp/control/basicevent1", HTTP_POST, [this](){
    String request = this->http.arg(0);
    LOGN("Responding to basicevent1...\nRequest:"); LOGN(request);
    if (request.indexOf("<BinaryState>1</BinaryState>") >= 0) {
      LOGN("Turn-on request");
      switchOn(true);
    }
    if (request.indexOf("<BinaryState>0</BinaryState>") >= 0) {
      LOGN("Turn-off request");
      switchOn(false);
    }
    http.send(200, "text/plain", "");
  });

  http.on("/eventservice.xml", HTTP_GET, [this](){
    LOGN("Responding to /eventservice.xml...");
    http.send(200, "text/plain",
      "<?scpd xmlns=\"urn:Belkin:service-1-0\"?>"
      "<actionList>"
        "<action>"
          "<name>SetBinaryState</name>"
          "<argumentList>"
            "<argument>"
              "<retval/>"
              "<name>BinaryState</name>"
              "<relatedStateVariable>BinaryState</relatedStateVariable>"
              "<direction>in</direction>"
            "</argument>"
          "</argumentList>"
           "<serviceStateTable>"
            "<stateVariable sendEvents=\"yes\">"
              "<name>BinaryState</name>"
              "<dataType>Boolean</dataType>"
              "<defaultValue>0</defaultValue>"
            "</stateVariable>"
            "<stateVariable sendEvents=\"yes\">"
              "<name>level</name>"
              "<dataType>string</dataType>"
              "<defaultValue>0</defaultValue>"
            "</stateVariable>"
          "</serviceStateTable>"
        "</action>"
      "</scpd>\r\n"
      "\r\n"
    );
  });
  
  http.on("/setup.xml", HTTP_GET, [this](){
    LOGN("Responding to /setup.xml...");
    http.send(200, "text/xml", (String() + 
        "<?xml version=\"1.0\"?>"
        "<root>"
          "<device>"
            "<deviceType>urn:Belkin:device:controllee:1</deviceType>"
            "<friendlyName>"+device_name+"</friendlyName>"
            "<manufacturer>Belkin International Inc.</manufacturer>"
            "<modelName>Emulated Socket</modelName>"
            "<modelNumber>3.1415</modelNumber>"
            "<UDN>uuid:"+persistent_uuid+"</UDN>"
            "<serialNumber>221517K0101769</serialNumber>"
            "<binaryState>0</binaryState>"
            "<serviceList>"
              "<service>"
                "<serviceType>urn:Belkin:service:basicevent:1</serviceType>"
                "<serviceId>urn:Belkin:serviceId:basicevent1</serviceId>"
                "<controlURL>/upnp/control/basicevent1</controlURL>"
                "<eventSubURL>/upnp/event/basicevent1</eventSubURL>"
                "<SCPDURL>/eventservice.xml</SCPDURL>"
              "</service>"
            "</serviceList>" 
          "</device>"
        "</root>\r\n"
        "\r\n"
      ).c_str());
  });
  
  http.begin();
  LOGN("HTTP server started for " + device_name + " on port " + String(port) + "...");
}


void WeMoSwitchEmulator::handlePackets() {
  http.handleClient();
}
