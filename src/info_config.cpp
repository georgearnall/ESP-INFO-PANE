#include "info_config.h"
#include <Preferences.h>

char username[40];
char password[40];
char location[5];

void setupConfig() {
    Preferences preferences;
    Serial.println("loading config from preferences");
    preferences.begin("info-pane", true);
    strcpy(username, preferences.getString("rttapi_username", "").c_str());
    strcpy(password, preferences.getString("rttapi_password", "").c_str());
    strcpy(location, preferences.getString("rttapi_location", "SKW").c_str());
    preferences.end();
    Serial.println(username);
    Serial.println(password);
    Serial.println(location);
}    

void saveConfig(String username, String password, String location) {
    Preferences preferences;
    //save the custom parameters to Preferences
    Serial.println("saving config");
    preferences.begin("info-pane", false);
    preferences.putString("rttapi_username", username);
    preferences.putString("rttapi_password", password);
    preferences.putString("rttapi_location", location);
    preferences.end();
}

String getUsername() {
    return String(username);
}

String getPassword() {
    return String(password);
}

String getLocation() {
    return String(location);
}
