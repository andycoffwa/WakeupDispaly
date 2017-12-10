#ifndef TimeClient_H

#define TimeClient_H

#include <ESP8266WiFi.h>
#include "ConfigClient.h"

class TimeClient {

  time_t localDateTime;

public:
  TimeClient(void);
  void initTimeClient(ConfigClient configClient);
  void loop(void);
  void toSerial(void);
};

#endif
