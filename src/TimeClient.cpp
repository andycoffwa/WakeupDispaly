#include "ArduinoJson.h"
#include <ESP8266WiFi.h>

String urldecode(String str);
String urlencode(String str);
unsigned char h2int(char c);

const char* server = "api.openweathermap.org";
const int httpPort = 80;

void TimeClient_Init(void){
  Serial.println("TimeClient_Inited");
  StaticJsonBuffer<2000> jsonBuffer;
  WiFiClient client;

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to weather API");
    // Make a HTTP request:
    client.println("GET /data/2.5/weather?id=6619279&units=metric&appid=7af4c691121b4c89c797436bbdd22389 HTTP/1.1");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  }

  String json = "";
  bool headersReceived = false;
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      headersReceived = true;
      Serial.println("headers received");
    }
    if (headersReceived) {
      json.concat(line);
    }
  }
  Serial.println(json);
}

/*

String urldecode(String str)
{

    String encodedString="";
    char c;
    char code0;
    char code1;
    for (int i =0; i < str.length(); i++){
        c=str.charAt(i);
      if (c == '+'){
        encodedString+=' ';
      }else if (c == '%') {
        i++;
        code0=str.charAt(i);
        i++;
        code1=str.charAt(i);
        c = (h2int(code0) << 4) | h2int(code1);
        encodedString+=c;
      } else{

        encodedString+=c;
      }

      yield();
    }

   return encodedString;
}

String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;

}

unsigned char h2int(char c)
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}
*/
