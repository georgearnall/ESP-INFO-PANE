#include "info_display.h"
#include <Fonts/FreeMonoBold9pt7b.h>
#include <GxEPD2_4G_4G.h>

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
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawRoundRect(utx+tbx-ALERT_PADDING_X, uty+tby-ALERT_PADDING_Y, tbw+ALERT_PADDING_X+ALERT_PADDING_X, tbh+ALERT_PADDING_Y+ALERT_PADDING_Y, ALERT_RADIUS, GxEPD_DARKGREY);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(utx, uty);
    display.print(message);
  }
  while (display.nextPage());
}

void helloFourGreyLevels()
{
  Serial.println("helloFourGreyLevels");
  const char fourgrey[] = "four grey levels";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  const char HelloWorld[] = "Hello World!";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(3);
  display.setFont(&FreeMonoBold9pt7b);
  // do this outside of the loop
  int16_t tbx, tby; uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fourgrey, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  // center update mode
  display.getTextBounds(spm, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) / 2) - tby;
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(hwx, hwy);
    display.print(HelloWorld);
    display.setTextColor(GxEPD_DARKGREY);
    display.setCursor(utx, uty);
    display.print(fourgrey);
    display.setTextColor(GxEPD_LIGHTGREY);
    display.setCursor(umx, umy);
    display.print(display.epd2.hasPartialUpdate ? spm : npm );
  }
  while (display.nextPage());

  Serial.println("helloFourGreyLevels done");
}