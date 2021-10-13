// -----------------------------------------------------------------------------------
// Polling serial IP for ESP32
#pragma once

#include "../../Common.h"

#if defined(OPERATIONAL_MODE) && OPERATIONAL_MODE == WIFI

#if defined(ESP32) && (SERIAL_IP_MODE == STATION || SERIAL_IP_MODE == ACCESS_POINT)

  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WiFiAP.h>

  class IPSerial : public Stream {
    public:
      inline void begin() { begin(9999); }
      void begin(long port);
      
      void end();

      int read(void);

      int available(void);

      int peek(void);

      void flush(void);

      size_t write(uint8_t data);

      size_t write(const uint8_t* data, size_t count);

      inline size_t write(unsigned long n) { return write((uint8_t)n); }
      inline size_t write(long n) { return write((uint8_t)n); }
      inline size_t write(unsigned int n) { return write((uint8_t)n); }
      inline size_t write(int n) { return write((uint8_t)n); }

      using Print::write;

    private:
      WiFiServer *cmdSvr;
      WiFiClient cmdSvrClient;

      int port = -1;
      unsigned long timeout = 60000;
      unsigned long clientTimeout = 0;
      bool resetTimeout = false;

      bool accessPointEnabled = SERIAL_IP_MODE == ACCESS_POINT;
      bool stationEnabled     = SERIAL_IP_MODE == STATION || SERIAL_IP_MODE == STATION_DHCP;
      bool stationDhcpEnabled = SERIAL_IP_MODE == STATION_DHCP;

      char wifi_sta_ssid[40] = STA_SSID;
      char wifi_sta_pwd[40] = STA_PASSWORD;

      IPAddress wifi_sta_ip = IPAddress STA_IP_ADDR;
      IPAddress wifi_sta_gw = IPAddress STA_GW_ADDR;
      IPAddress wifi_sta_sn = IPAddress STA_SN_MASK;

      char wifi_ap_ssid[40] = AP_SSID;
      char wifi_ap_pwd[40] = AP_PASSWORD;
      byte wifi_ap_ch = AP_CHANNEL;

      IPAddress wifi_ap_ip = IPAddress AP_IP_ADDR;
      IPAddress wifi_ap_gw = IPAddress AP_GW_ADDR;
      IPAddress wifi_ap_sn = IPAddress AP_SN_MASK;
  };

  #if STANDARD_COMMAND_CHANNEL == ON
    extern IPSerial ipSerial;
    #define SERIAL_IP ipSerial
  #endif

  #if PERSISTENT_COMMAND_CHANNEL == ON
    extern IPSerial pipSerial;
    #define SERIAL_PIP pipSerial
  #endif

#endif

#endif
