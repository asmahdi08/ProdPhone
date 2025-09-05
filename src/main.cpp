#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <WiFi.h>
#include "time.h"
#include "Utils/TimeUtils.h"
#include "Definitions.h"
#include "Utils/Logging/Logging.h"

#include "Drawers.h"

#include "Screens/ScreenManager.h"
#include "Screens/ScreenRegistries.h"



const char* ssid     = "Mahdi";
const char* password = "22012008..";
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 6*3600; // Bangladesh is GMT+6
const int daylightOffset_sec = 0;

unsigned long lastUpdate = 0;

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// put function declarations here:
void drawTopBar();
void drawBasicExample();
void setupTime();

ScreenManager screenManager;
ScreenRegistries screenRegistries;
Logger logger;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(L_BTN_PIN, INPUT_PULLUP);
  pinMode(R_BTN_PIN, INPUT_PULLUP);
  tft.init();
  tft.fillScreen(TFT_BLACK);

  pp_drawText("Loading Time", 64, 90,
      TFT_GREEN,
      1,
      TFT_BLACK,
      MC_DATUM
  );

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  logger.log_info("WiFi connected.");
  
  // Configure NTP time synchronization
  setupTime();
  
  // Wait a bit for time sync
  delay(2000);

  tft.fillScreen(TFT_BLACK);

  drawTopBar();

  screenManager.setScreen(screenRegistries.getScreen(0)); // set to dashboard screen
  screenManager.draw();

}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate >= 1000) { // update every second
    lastUpdate = now;
    String timeStr = TimeUtils::getCurrentTime();

    pp_drawText(timeStr, 64, 2,
      TFT_GREEN,
      1,
      TFT_BLACK,
      TC_DATUM
    );

    
  }

  screenManager.update();

  int16_t screenId = screenManager.handleNavigation();

  if(screenId != -1) {
    screenManager.setScreen(screenRegistries.getScreen(screenId));
    screenManager.draw();
    Serial.println("Logs: " + logger.getLogs());
  }
}

// put function definitions here:

void drawTopBar(){

  pp_drawText("Wifi:", 2, 2,
      TFT_GREEN,
      1,
      TFT_BLACK,
      TL_DATUM
  );

  pp_drawText("09:30", 64, 2,
      TFT_GREEN,
      1,
      TFT_BLACK,
      TC_DATUM
  );

  pp_drawText("68%", 126, 2,
      TFT_GREEN,
      1,
      TFT_BLACK,
      TR_DATUM
  );

  tft.setCursor(12, 0);
  tft.drawLine(0, 13, 128, 13, TFT_GREEN);
}

void setupTime() {
  logger.log_info("Configuring time with NTP servers...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  
  // Wait for time to be set
  logger.log_info("Waiting for NTP time sync...");
  struct tm timeinfo;
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts < 10) {
    logger.log_info(".");
    delay(1000);
    attempts++;
  }
  
  if (attempts < 10) {
    Serial.println(" Time synchronized!");
    Serial.print("Current time: ");
    char buf[30];
    strftime(buf, sizeof(buf), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    Serial.println(buf);
  } else {
    Serial.println(" Time sync failed!");
  }
}


