#ifndef ConfigClient_H

#define ConfigClient_H

#include <ESP8266WiFi.h>

class ConfigClient {

  String location;
  String timezone;
  String wakeupTime;

public:
  ConfigClient(void);
  String getLocation(void){return location;};
  String getTimezone(void){return timezone;};
  String getWakeupTime(void){return wakeupTime;};
  void toSerial (void);
};

#endif
