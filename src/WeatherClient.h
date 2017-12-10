#ifndef WeatherClient_H

#define WeatherClient_H

#include <ESP8266WiFi.h>
#include "ConfigClient.h"

class WeatherClient {  

public:
  WeatherClient(void);
  void initWeatherClient(ConfigClient configClient);
  void loop(void);
  void toSerial(void);
};

#endif
