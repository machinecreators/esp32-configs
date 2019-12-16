#include <Wire.h>
#include <U8g2lib.h>
#include <WiFi.h>

#include "strformat/strformat.h"

#define BOARD 0

#if (BOARD == 0)
  #include "boards/ttgo_t_eight_oled.h"
  U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, OLED_SCL, OLED_SDA);
#elif (BOARD == 1)
  #include "boards/wemos_lolin_oled.h"
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);
#elif (BOARD == 2)
  #include "boards/ttgo_oled.h"
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);
#elif (BOARD == 3)
  #include "boards/green_board.h"
  //U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);
  U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, OLED_SCL, OLED_SDA, OLED_CS, OLED_DC, OLED_RESET);
  //U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(U8G2_R0, OLED_SCL, OLED_SDA, OLED_CS, OLED_DC, OLED_RESET);
#endif

void WifiScan() {
  if (LED_BUILTIN >= 0) digitalWrite(LED_BUILTIN, 1);
  int n = WiFi.scanNetworks();
  if (LED_BUILTIN >= 0) digitalWrite(LED_BUILTIN, 0);

  if (n == 0) {
    u8g2.clearBuffer();
    u8g2.drawStr(20, 20,"No network found.");
    u8g2.sendBuffer();
  } else {
    u8g2.clearBuffer();
    for(int i = 0; i < n; ++i)
    {
      u8g2.drawStr(20, 8 * (i+1), vformat("%u: %.6s (%i) %c", i, WiFi.SSID(i).c_str(), WiFi.RSSI(i), (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? ' ': '*').c_str());
    }
    u8g2.sendBuffer();
  }
}


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  u8g2.begin();
  u8g2.setContrast(5);
  u8g2.setFont(u8g2_font_profont10_tr);

  if (LED_BUILTIN >= 0) pinMode(LED_BUILTIN, OUTPUT);
  
  //pinMode(BTN_A, INPUT_PULLUP);
  //pinMode(BTN_B, INPUT_PULLUP);
  //pinMode(BTN_C, INPUT_PULLUP);
}

void loop() {
  WifiScan();
  delay(5000);
}

