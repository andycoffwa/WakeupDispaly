#include "ArduinoJson.h"
#include "ConfigClient.h"
#include <ESP8266WiFi.h>

const char* configServer = "s3-ap-southeast-2.amazonaws.com";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
//const char* fingerprint = "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C";
const char* fingerprint = "EA DF 49 81 49 50 6B 09 9A FF 0A 98 9B B9 EC C0 8E 1E EA A6";

ConfigClient::ConfigClient(){
  Serial.println("[INFO] ConfigClient created");
  StaticJsonBuffer<300> jsonBuffer;
  WiFiClientSecure client;

  Serial.println("\n[INFO] Starting connection to configServer...");
  if (!client.connect(configServer, httpsPort)) {
    Serial.println("[ERROR] connection failed");
    return;
  }

  if (client.verify(fingerprint, configServer)) {
    Serial.println("[INFO] certificate matches");
  } else {
    Serial.println("[ERROR] certificate doesn't match");
  }

  // if you get a connection, report back via serial:
  if (client.connect(configServer, httpsPort)) {
    Serial.println("[INFO] connected to s3 config file");
    // Make a HTTP request:
    client.println("GET /wakeup-timer/config.json HTTP/1.1");
    client.println("Host: s3-ap-southeast-2.amazonaws.com");
    client.println("Connection: close");
    client.println();
  }

  String json = "";
  bool headersReceived = false;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      headersReceived = true;
      //Serial.println("headers received");
    }
    if (headersReceived) {
      json.concat(line);
    }
  }

  JsonObject& jsonObj = jsonBuffer.parseObject(json);
  //const char* locationChar = jsonObj["location"].as<const char*>();
  //location = String(locationChar);
  location = String(jsonObj["location"].as<const char*>());
  timezone = String(jsonObj["timezone"].as<const char*>());
  wakeupTime = String(jsonObj["wake-up-time"].as<const char*>());
}

void ConfigClient::toSerial(void){
  Serial.println("[INFO] Config");
  Serial.print("location: ");
  Serial.println(location);
  Serial.print("timezone: ");
  Serial.println(timezone);
  Serial.print("wake up time: ");
  Serial.println(wakeupTime);
  Serial.println("End config");
}
