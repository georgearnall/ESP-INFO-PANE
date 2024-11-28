#ifndef INFO_DISPLAY_H
#define INFO_DISPLAY
#include <Arduino.h> 

void setupDisplay();

void displayAlert(String &message);

void displayStatusMessage(String &message);

#endif