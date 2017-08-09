#pragma once

//#define ENABLE_TRACE
#ifdef ENABLE_TRACE
  #define LOGN(msg) Serial.println(msg);
  #define LOG(msg) Serial.print(msg);
#else
  #define LOGN(msg)
  #define LOG(msg)
#endif
