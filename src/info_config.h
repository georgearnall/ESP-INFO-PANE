#ifndef INFO_Config_H
#define INFO_Config
#include <Arduino.h> 
#include <WiFiManager.h>

void setupConfig();

void saveConfig(String username, String password, String location);

String getUsername();

String getPassword();

String getLocation();

#endif