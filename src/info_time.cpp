#include "info_time.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setupTime() {
  timeClient.begin();
}

void updateTime() {
  Serial.println("Updating time");
  timeClient.update();
}

String getTimeString() {
    return timeClient.getFormattedTime();
}