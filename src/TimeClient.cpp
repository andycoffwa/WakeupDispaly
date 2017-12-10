// TODO Fix timezone in url for timezone api

#include "ArduinoJson.h"
#include <ESP8266WiFi.h>
#include "TimerObject.h"
#include "Time.h"
#include "TimeClient.h"

time_t localDateTime;

TimerObject *clockTimer = new TimerObject(3600000);
String status;
const char* localDateTimeStr;

const char* timeServer = "api.timezonedb.com";
const int httpPort = 80;
const int httpsPort = 443;

ConfigClient t_configClient;

void syncTime(void);

TimeClient::TimeClient(void){

}

void TimeClient::initTimeClient(ConfigClient configClient){
  t_configClient = configClient;
  syncTime();
	clockTimer->setOnTimer(&syncTime);
	clockTimer->Start(); //start the thread.
}

void TimeClient::loop(void){
  clockTimer->Update();
}

void saveTime (String localDateTimeStr){

  int start, end, year, month, day, hour, minute, second = 0;

  end = localDateTimeStr.indexOf("-",start);
  year = localDateTimeStr.substring(start, end).toInt();
  start = end + 1;
  end = localDateTimeStr.indexOf("-", start);
  month  = localDateTimeStr.substring(start, end).toInt();
  start = end + 1;
  end = localDateTimeStr.indexOf(" ");
  day = localDateTimeStr.substring(start, end).toInt();
  start = end + 1;
  end = localDateTimeStr.indexOf(":", start);
  hour = localDateTimeStr.substring(start, end).toInt();
  start = end + 1;
  end = localDateTimeStr.indexOf(":", start);
  minute = localDateTimeStr.substring(start, end).toInt();
  start = end + 1;
  end = localDateTimeStr.length();
  second = localDateTimeStr.substring(start, end).toInt();

  setTime(hour, minute, second, day, month, year);
  localDateTime = now();
}

void syncTime(void){
  StaticJsonBuffer<600> jsonBuffer;
  WiFiClient client;

  String zone = t_configClient.getTimezone();

  Serial.print("\n[INFO] Starting connection to ");
  Serial.println(timeServer);
  // if you get a connection, report back via serial:
  if (client.connect(timeServer, httpPort)) {
    Serial.println("[INFO] connected to timezone API");
    // Make a HTTP request:
    client.println("GET /v2/get-time-zone?key=5T7J6OVIZGUW&format=json&zone=Australia/Sydney&by=zone HTTP/1.1");
    client.println("Host: api.timezonedb.com");
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
  //jsonObj.prettyPrintTo(Serial);
  status = String(jsonObj["status"].as<const char*>());
  localDateTimeStr = jsonObj["formatted"].as<const char*>();
  saveTime(String(localDateTimeStr));
}

void TimeClient::toSerial(void){
  Serial.println("[INFO] Time Client ");
  Serial.print("Status: ");
  Serial.println(status);
  Serial.print("Local date time: ");
  Serial.println(localDateTime);
  Serial.print("Year: ");
  Serial.println(year());
  Serial.print("Month: ");
  Serial.println(month());
  Serial.print("Day: ");
  Serial.println(day());
  Serial.print("Hour: ");
  Serial.println(hour());
  Serial.print("Minute: ");
  Serial.println(minute());
  Serial.print("Second: ");
  Serial.println(second());
  Serial.println("End Client");
}
