#include "Application.h"
#include "Wifi.h"
#include "TimeClient.h"

void Application_Init(void)
{
    Serial.println("Init WakeupDisplay application");
    Wifi_Init();
    TimeClient_Init();
    //NTPClient_PeriodicNTPCheckInit();   //initialise NTP   periodic update routine
//  be_Indicators_Init();
//  be_MQTT_Init();
//  be_EnergyMonitoring_Init();
//  be_InputControl_Init();
//  be_OutputControl_Init();
//  be_MQTT_Subscriptions_Init();
}

void Application_MainLoop(void)
{
    //Application_Init();
    delay(10000);
//  be_MQTT_MainLoop();
//  be_EnergyMonitoring_MainLoop();
//  be_InputControl_MainLoop();
//  be_OutputControl_MainLoop();
    //NTPClient_MainLoop(); //checks to see if locally kept time needs to be updated from NTP server
//  be_MQTT_Subscriptions_MainLoop();
//  be_Indicators_MainLoop();
}
