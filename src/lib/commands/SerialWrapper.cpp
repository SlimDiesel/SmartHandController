// -----------------------------------------------------------------------------------
// SerialWrapper a single class to allow uniform access to other serial port classes

#include "SerialWrapper.h"

#ifdef ESP32
  #include "../serial/Serial_IP_ESP32.h"
#endif
#include "../serial/Serial_IP_Ethernet.h"

#ifdef MOUNT_PRESENT
  #if ST4_AUX_INTERFACE == ON && ST4_HAND_CONTROL == ON
    #include "../serial/Serial_ST4_Master.h"
  #endif
  #include "../serial/Serial_Local.h"
#endif

#if SERIAL_ONSTEP == HardSerial
  #undef SERIAL_ONSTEP
  HardwareSerial HWSerialA(SERIAL_ONSTEP_RX, SERIAL_ONSTEP_TX);
  #define SERIAL_ONSTEP HWSerialA
  #define SERIAL_ONSTEP_RXTX_SET
#endif

#if SERIAL_B == HardSerial
  #undef SERIAL_B
  HardwareSerial HWSerialB(SERIAL_B_RX, SERIAL_B_TX);
  #define SERIAL_B HWSerialB
  #define SERIAL_B_RXTX_SET
#endif


SerialWrapper::SerialWrapper() {
  static uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_B
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_C
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_D
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_ST4
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_BT
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_IP
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_PIP
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
  #ifdef SERIAL_LOCAL
    if (!hasChannel(channel)) { thisChannel = channel; setChannel(channel); return; }
    channel++;
  #endif
}

void SerialWrapper::begin() { begin(9600); }

void SerialWrapper::begin(long baud) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++))
      #if defined(SERIAL_ONSTEP_RX) && defined(SERIAL_ONSTEP_TX) && !defined(SERIAL_ONSTEP_RXTX_SET)
        SERIAL_ONSTEP.begin(baud, SERIAL_8N1, SERIAL_ONSTEP_RX, SERIAL_ONSTEP_TX);
      #else
        SERIAL_ONSTEP.begin(baud);
      #endif
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++))
      #if defined(SERIAL_B_RX) && defined(SERIAL_B_TX) && !defined(SERIAL_B_RXTX_SET)
        SERIAL_B.begin(baud, SERIAL_8N1, SERIAL_B_RX, SERIAL_B_TX);
      #else
        SERIAL_B.begin(baud);
      #endif
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++))
      #if defined(SERIAL_C_RX) && defined(SERIAL_C_TX) && !defined(SERIAL_C_RXTX_SET)
        SERIAL_C.begin(baud, SERIAL_8N1, SERIAL_C_RX, SERIAL_C_TX);
      #else
        SERIAL_C.begin(baud);
      #endif
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++))
      #if defined(SERIAL_D_RX) && defined(SERIAL_D_TX) && !defined(SERIAL_D_RXTX_SET)
        SERIAL_D.begin(baud, SERIAL_8N1, SERIAL_D_RX, SERIAL_D_TX);
      #else
        SERIAL_D.begin(baud);
      #endif
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) SERIAL_ST4.begin(baud);
  #endif
  #ifdef SERIAL_BT
    //if (isChannel(channel++)) SERIAL_BT.begin(SERIAL_BT_NAME); // started early in .ino file
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) SERIAL_IP.begin(9999);
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) SERIAL_PIP.begin(9999);
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) SERIAL_LOCAL.begin(baud);
  #endif
}

void SerialWrapper::end() {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) SERIAL_ONSTEP.end();
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) SERIAL_B.end();
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) SERIAL_C.end();
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) SERIAL_D.end();
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) SERIAL_ST4.end();
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) SERIAL_BT.end();
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) SERIAL_IP.end();
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) SERIAL_PIP.end();
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) SERIAL_LOCAL.end();
  #endif
}

size_t SerialWrapper::write(uint8_t data) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) return SERIAL_ONSTEP.write(data);
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) return SERIAL_B.write(data);
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) return SERIAL_C.write(data);
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) return SERIAL_D.write(data);
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) return SERIAL_ST4.write(data);
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) return SERIAL_BT.write(data);
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) return SERIAL_IP.write(data);
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) return SERIAL_PIP.write(data);
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) return SERIAL_LOCAL.write(data);
  #endif
  return -1;
}

size_t SerialWrapper::write(const uint8_t *data, size_t quantity) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) return SERIAL_ONSTEP.write(data, quantity);
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) return SERIAL_B.write(data, quantity);
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) return SERIAL_C.write(data, quantity);
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) return SERIAL_D.write(data, quantity);
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) return SERIAL_ST4.write(data, quantity);
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) return SERIAL_BT.write(data, quantity);
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) return SERIAL_IP.write(data, quantity);
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) return SERIAL_PIP.write(data, quantity);
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) return SERIAL_LOCAL.write(data, quantity);
  #endif
  return -1;
}

int SerialWrapper::available(void) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) return SERIAL_ONSTEP.available();
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) return SERIAL_B.available();
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) return SERIAL_C.available();
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) return SERIAL_D.available();
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) return SERIAL_ST4.available();
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) return SERIAL_BT.available();
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) return SERIAL_IP.available();
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) return SERIAL_PIP.available();
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) return SERIAL_LOCAL.available();
  #endif
  return 0;
}

int SerialWrapper::read(void) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) return SERIAL_ONSTEP.read();
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) return SERIAL_B.read();
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) return SERIAL_C.read();
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) return SERIAL_D.read();
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) return SERIAL_ST4.read();
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) return SERIAL_BT.read();
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) return SERIAL_IP.read();
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) return SERIAL_PIP.read();
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) return SERIAL_LOCAL.read();
  #endif
  return -1;
}

int SerialWrapper::peek(void) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) return SERIAL_ONSTEP.peek();
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) return SERIAL_B.peek();
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) return SERIAL_C.peek();
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) return SERIAL_D.peek();
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) return SERIAL_ST4.peek();
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) return SERIAL_BT.peek();
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) return SERIAL_IP.peek();
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) return SERIAL_PIP.peek();
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) return SERIAL_LOCAL.peek();
  #endif
  return -1;
}

void SerialWrapper::flush(void) {
  uint8_t channel = 0;
  #ifdef SERIAL_ONSTEP
    if (isChannel(channel++)) SERIAL_ONSTEP.flush();
  #endif
  #ifdef SERIAL_B
    if (isChannel(channel++)) SERIAL_B.flush();
  #endif
  #ifdef SERIAL_C
    if (isChannel(channel++)) SERIAL_C.flush();
  #endif
  #ifdef SERIAL_D
    if (isChannel(channel++)) SERIAL_D.flush();
  #endif
  #ifdef SERIAL_ST4
    if (isChannel(channel++)) SERIAL_ST4.flush();
  #endif
  #ifdef SERIAL_BT
    if (isChannel(channel++)) SERIAL_BT.flush();
  #endif
  #ifdef SERIAL_IP
    if (isChannel(channel++)) SERIAL_IP.flush();
  #endif
  #ifdef SERIAL_PIP
    if (isChannel(channel++)) SERIAL_PIP.flush();
  #endif
  #ifdef SERIAL_LOCAL
    if (isChannel(channel++)) SERIAL_LOCAL.flush();
  #endif
}
