#ifndef INFO_WIFI_H
#define INFO_WIFI
#include <Arduino.h>
#include <WiFi.h>
 
void setupWifi();

String getWifiStatusMessage(wl_status_t status);

#endif