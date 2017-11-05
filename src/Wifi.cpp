#include "Wifi.h"
#include <ESP8266WiFi.h>

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "coffey"
#define WLAN_PASS       "CoffeyPeel1"

/******************************************************************************/

void displayConnectionDetails(void);

void Wifi_Init(void)
{


  Serial.println(F("Attempting to connecto to wifi"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");  
  displayConnectionDetails();
}

/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
void displayConnectionDetails(void)
{
  IPAddress  ipAddress, netmask, gateway, dhcpserv, dnsserv;
  Serial.print(F("\nIP Addr: ")); ipAddress = WiFi.localIP(); Serial.println(ipAddress);
  Serial.print(F("\nNetmask: ")); netmask = WiFi.subnetMask(); Serial.println(netmask);
  Serial.print(F("\nGateway: ")); gateway = WiFi.gatewayIP();; ; Serial.println(gateway);
  //Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
  //Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
  Serial.println();


}

