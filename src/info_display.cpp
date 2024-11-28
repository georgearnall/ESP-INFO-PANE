#include "info_display.h"
#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxEPD2_4G_4G.h>

void _printMultiline(String text, int16_t x, int16_t y, int16_t maxWidth);
void _printMultilineTextCentered(String text, int16_t y, int16_t maxWidth);

const uint8_t PIN_EPD_BUSY  = 13;
const uint8_t PIN_EPD_CS    = 27;
const uint8_t PIN_EPD_RST   = 12;
const uint8_t PIN_EPD_DC    = 14;

#define MAX_DISPLAY_BUFFER_SIZE 65536ul // e.g.
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 4) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 4))

GxEPD2_4G_4G<GxEPD2_750_T7, MAX_HEIGHT(GxEPD2_750_T7)> display
        (GxEPD2_750_T7(PIN_EPD_CS, PIN_EPD_DC, PIN_EPD_RST, PIN_EPD_BUSY));

const uint8_t ALERT_PADDING_X  = 50;
const uint8_t ALERT_PADDING_Y  = 20;
const uint8_t ALERT_RADIUS  = 10;

void setupDisplay() {
    display.init(115200);
    display.setRotation(3);
    display.setTextSize(2);
}

void displayAlert(String &message)
{
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(message, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby; // display in upper half of screen
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawRoundRect(utx+tbx-ALERT_PADDING_X, uty+tby-ALERT_PADDING_Y, tbw+ALERT_PADDING_X+ALERT_PADDING_X, tbh+ALERT_PADDING_Y+ALERT_PADDING_Y, ALERT_RADIUS, GxEPD_DARKGREY);
    display.setTextColor(GxEPD_BLACK);
    _printMultilineTextCentered(message, uty, display.width());
  }
  while (display.nextPage());
}
void _printMultiline(String text, int16_t x, int16_t y, int16_t maxWidth) {
    String line = "";
    for (int i = 0; i < text.length(); i++) {
        line += text[i];
        int16_t tbX, tbY;
        uint16_t tbW, tbH;
        if (line.length() == 1 && text[i] == '\n') {
            // If the line is empty, calculate the bounds based arbitrary text
            display.getTextBounds("A", 0, y, &tbX, &tbY, &tbW, &tbH);
        } else {
            // If the line has content, calculate the bounds based on the current line
            display.getTextBounds(line, 0, y, &tbX, &tbY, &tbW, &tbH);
        }
        if (tbW > maxWidth || text[i] == '\n') {
            display.setCursor(x, y);
            display.print(line);
            line = "";
            y += tbH + 2; // Move cursor down for next line
        }
    }
    if (line.length() > 0) {
        display.setCursor(x, y);
        display.print(line);
    }
}

void _printMultilineTextCentered(String text, int16_t y, int16_t maxWidth) {
    String line = "";
    int16_t x;
    for (int i = 0; i < text.length(); i++) {
        line += text[i];

        // Calculate bounds of the current line
        int16_t tbX, tbY;
        uint16_t tbW, tbH;
        if (line.length() == 1 && text[i] == '\n') {
            // If the line is empty, calculate the bounds based arbitrary text
            display.getTextBounds("A", 0, y, &tbX, &tbY, &tbW, &tbH);
        } else {
            // If the line has content, calculate the bounds based on the current line
            display.getTextBounds(line, 0, y, &tbX, &tbY, &tbW, &tbH);
        }
        // Check if the line exceeds the max width or ends with '\n'
        if (tbW > maxWidth || text[i] == '\n') {
            // Calculate the starting x position to center the text
            x = (maxWidth - tbW) / 2;

            // Print the line centered
            display.setCursor(x, y);
            display.print(line);

            // Move to the next line
            line = "";
            y += tbH + 2; // Adjust vertical spacing
        }
    }

    // Print the last line if any content is left
    if (line.length() > 0) {
        int16_t tbX, tbY;
        uint16_t tbW, tbH;
        display.getTextBounds(line, 0, y, &tbX, &tbY, &tbW, &tbH);

        // Calculate the starting x position to center the text
        x = (maxWidth - tbW) / 2;

        display.setCursor(x, y);
        display.print(line);
    }
}

#define STATUS_MESSAGE_PADDING_X  8
void displayStatusMessage(String &message)
{
    Serial.println("displayStatusMessage");
    Serial.println(message);

    // Partial Update bottom 8px of screen
    int16_t y = display.height() - 16;
    display.setPartialWindow(0, y, display.width(), 16);
    display.setTextSize(1);

    int16_t tbx, tby; uint16_t tbw, tbh;
    display.getTextBounds(message, 0, y, &tbx, &tby, &tbw, &tbh);
    display.firstPage();
    do
    {
        display.fillRect(0,  y, display.width(), 16, GxEPD_WHITE);
        display.setTextColor(GxEPD_DARKGREY);
        display.setCursor(display.width() - tbw - STATUS_MESSAGE_PADDING_X, y); // right align
        display.print(message);
    }
    while (display.nextPage());
}