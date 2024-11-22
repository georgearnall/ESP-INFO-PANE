#include "info_display.h"
// #include "wifi.h"
#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");
    delay(100);

    setupDisplay();
    
    String message = String("Connect to WiFi...");
    displayAlert(message);
}

void loop() {}
