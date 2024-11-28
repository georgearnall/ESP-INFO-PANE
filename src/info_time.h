#ifndef INFO_TIME_H
#define INFO_TIME
#include <Arduino.h> 
#include <WiFiManager.h>

void setupTime();

void updateTime();

String getTimeString();

#endif