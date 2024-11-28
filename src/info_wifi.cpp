#include "info_wifi.h"
#include "info_config.h"
#include <WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <Arduino.h>

char rttapi_username[40];
char rttapi_password[40];
char rttapi_location[5];

bool shouldSaveConfig = false;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void saveConfigFromWiFiManager() {
}

void setupWifi() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.
 
    // put your setup code here, to run once:
    Serial.begin(115200);
    
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

    setupConfig();
    strcpy(rttapi_username, getUsername().c_str());
    strcpy(rttapi_password, getPassword().c_str());
    strcpy(rttapi_location, getLocation().c_str());
 
    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();
 
    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    WiFiManagerParameter custom_rttapi_username("rttapi_username", "RTT API Username", rttapi_username, 40);
    WiFiManagerParameter custom_rttapi_password("rttapi_password", "RTT API Password", rttapi_password, 40);
    WiFiManagerParameter custom_rttapi_location("rttapi_location", "Location Code", rttapi_location, 5);
 
    wm.setSaveConfigCallback(saveConfigCallback);
    wm.addParameter(&custom_rttapi_username);
    wm.addParameter(&custom_rttapi_password);
    wm.addParameter(&custom_rttapi_location);

    bool res;
    res = wm.autoConnect("InfoPane", "infopane"); // password protected ap
 
    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        saveConfig(custom_rttapi_username.getValue(), 
                    custom_rttapi_password.getValue(), 
                    custom_rttapi_location.getValue());
    }
}

String getWifiStatusMessage(wl_status_t status) {
    switch(status) {
        case WL_SCAN_COMPLETED:
            return String("Scan Completed");
        case WL_CONNECTED:
            return String("Connected to:\n\n") + WiFi.SSID();
        case WL_CONNECT_FAILED:
            return String("Connected Failed");
        case WL_DISCONNECTED:
            return String("Disconnected");
        case WL_CONNECTION_LOST:
            return String("Connected Lost");
        default:
            return String("Connect to WiFi... \n\nSSID: InfoPane\nPASS: infopane");
    }
}