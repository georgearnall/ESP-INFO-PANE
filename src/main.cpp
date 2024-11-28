#include "info_display.h"
#include "info_wifi.h"
#include "info_time.h"
#include <Arduino.h>
#include <WiFi.h>

void checkDisplayWifiStatus();

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");
    delay(100);
    setupDisplay();
    checkDisplayWifiStatus();
    setupWifi();
}


void loop() {
    checkDisplayWifiStatus();
    updateTime();

    displayStatusMessage(String("Updated: ") + getTimeString());

    delay(10000);
}

wl_status_t previousWifiStatus = WL_IDLE_STATUS;
void checkDisplayWifiStatus() {
    wl_status_t currentWifiStatus = WiFi.status();
    if (currentWifiStatus != previousWifiStatus) {
        previousWifiStatus = currentWifiStatus;
        String message = getWifiStatusMessage(currentWifiStatus);
        displayAlert(message);
    }
}