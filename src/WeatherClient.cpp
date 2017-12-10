#include "ArduinoJson.h"
#include <ESP8266WiFi.h>
#include "TimerObject.h"
#include "Time.h"
#include "WeatherClient.h"

TimerObject *weatherTimer = new TimerObject(60000);

const char* weatherServer = "api.openweathermap.org";
const int httpPort = 80;
const int httpsPort = 443;

ConfigClient w_configClient;

void syncWeather(void);

WeatherClient::WeatherClient(void){

}

void WeatherClient::initWeatherClient(ConfigClient configClient){
  w_configClient = configClient;
  syncWeather();
	weatherTimer->setOnTimer(&syncWeather);
	weatherTimer->Start(); //start the thread.
}

void WeatherClient::loop(void){
  weatherTimer->Update();
}

void saveWeather (String localDateTimeStr){

  Serial.println("TODO save weather");
}

void syncWeather(void){
  StaticJsonBuffer<4660> jsonBuffer;
  WiFiClient client;

  String zone = w_configClient.getTimezone();

  Serial.print("\n[INFO] Starting connection to ");
  Serial.println(weatherServer);
  // if you get a connection, report back via serial:
  if (client.connect(weatherServer, httpPort)) {
    Serial.println("[INFO] connected to weather API");
    // Make a HTTP request:
    client.println("GET /data/2.5/forecast?id=6619279&units=metric&cnt=6&appid=7af4c691121b4c89c797436bbdd22389 HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  }

  String json = "";
  bool startJsonBody = false;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line.indexOf('{') >= 0) {
      startJsonBody = true;
      //Serial.println("Json body detected");
    }
    if (startJsonBody) {
      json.concat(line);
    }
  }
  JsonObject& jsonObj = jsonBuffer.parseObject(json);
  jsonObj.prettyPrintTo(Serial);
  //status = String(jsonObj["status"].as<const char*>());

  //saveWeather(String(localDateTimeStr));
}

void WeatherClient::toSerial(void){
  // Serial.println("[INFO] Time Client ");
  // Serial.print("Status: ");
  // Serial.println(status);
  // Serial.print("Local date time: ");
  // Serial.println(localDateTime);
  // Serial.print("Year: ");
  // Serial.println(year());
  // Serial.print("Month: ");
  // Serial.println(month());
  // Serial.print("Day: ");
  // Serial.println(day());
  // Serial.print("Hour: ");
  // Serial.println(hour());
  // Serial.print("Minute: ");
  // Serial.println(minute());
  // Serial.print("Second: ");
  // Serial.println(second());
  // Serial.println("End Client");
}
