#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <WiFi.h>
#include "time.h"

#include "Drawers.h"

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

const char* ssid     = "Mahdi";
const char* password = "22012008..";
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = 6*3600; // Bangladesh is GMT+6
const int daylightOffset_sec = 0;

unsigned long lastUpdate = 0;

// put function declarations here:
void drawTopBar();
void drawBasicExample();
String getCurrentTime();
void setupTime();

#define L_BTN_PIN 19
#define R_BTN_PIN 21

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
  Serial.println("WiFi connected");
  
  // Configure NTP time synchronization
  setupTime();
  
  // Wait a bit for time sync
  delay(2000);

  tft.fillScreen(TFT_BLACK);

  uint8_t currentY = 25;
  int8_t lineHeight = 8; // size 4 font height + spacing

  drawTopBar();



  // Display current time
  String currentTime = getCurrentTime();
  pp_drawText(currentTime, 64, currentY,
      TFT_GREEN,
      4,
      TFT_BLACK,
      TC_DATUM
  );
  currentY += 4*lineHeight;

  pp_drawText("Tue Aug 26", 64, currentY,
      TFT_GREEN,
      1,
      TFT_BLACK,
      TC_DATUM
  );
  currentY += lineHeight+8;

  pp_drawBox(5, currentY,
      55,
      30,
      TFT_BLACK,
      TFT_GREEN
  );

  pp_drawBox(65, currentY,
      55,
      65,
      TFT_BLACK,
      TFT_GREEN
  );
  currentY += 35;

  pp_drawBox(5, currentY,
      55,
      30,
      TFT_BLACK,
      TFT_GREEN
  );
  currentY += 35;

  tft.drawLine(0, currentY, 128, currentY, TFT_GREEN);

  tft.drawLine(42, currentY, 42, 180, TFT_GREEN);
  tft.drawLine(84, currentY, 84, 180, TFT_GREEN);

}

void loop() {
  unsigned long now = millis();
  if (now - lastUpdate >= 1000) { // update every second
    lastUpdate = now;
    String timeStr = getCurrentTime();

    pp_drawText(timeStr, 64, 2,
      TFT_GREEN,
      1,
      TFT_BLACK,
      TC_DATUM
    );
    pp_drawText(timeStr, 64, 25,
      TFT_GREEN,
      4,
      TFT_BLACK,
      TC_DATUM
    );
  }
  // if(WiFi.status() != WL_CONNECTED) {
  //   Serial.println("WiFi Disconnected");
  // }else{
  //   Serial.println("WiFi Connected");
  // }
  if (digitalRead(L_BTN_PIN) == LOW) {
    Serial.println("Left button pressed");
  }
  if (digitalRead(R_BTN_PIN) == LOW) {
    Serial.println("Right button pressed");
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
  Serial.println("Configuring time with NTP servers...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
  
  // Wait for time to be set
  Serial.print("Waiting for NTP time sync: ");
  struct tm timeinfo;
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts < 10) {
    Serial.print(".");
    delay(1000);
    attempts++;
  }
  
  if (attempts < 10) {
    Serial.println(" Time synchronized!");
    Serial.print("Current time: ");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  } else {
    Serial.println(" Time sync failed!");
  }
}

String getCurrentTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return "--:--"; // fallback if time not available
  }

  char buf[6];
  strftime(buf, sizeof(buf), "%H:%M", &timeinfo); // format HH:MM
  Serial.print("Current time: ");
  Serial.println(buf);
  return String(buf);
}

void drawBasicExample(){
  // Text you want to display
  const char* txt = "09:30";
  int textSize = 3;  // scale up

  tft.setTextSize(textSize);

  // Built-in font: width = 6 px per char (5px + 1 spacing)
  int charWidth = 6 * textSize;
  int textWidth = strlen(txt) * charWidth;

  int x = (tft.width() - textWidth) / 2;  // horizontal center
  int y = 25; // vertical center, approx

  tft.setCursor(x, y);
  tft.print(txt);

  //draw a rounded box that has 3 lines "RAM: 30%", "ROM: 50%", "CPU: 70%"
  int boxX = 5;
  int boxY = 54;
  int boxWidth = 65;
  int boxHeight = 50;

  tft.fillRoundRect(boxX, boxY, boxWidth, boxHeight, 5, TFT_BLACK);
  tft.drawRoundRect(boxX, boxY, boxWidth, boxHeight, 5, TFT_GREEN);

  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(1);
  tft.setCursor(boxX + 5, boxY + 5);
  tft.println("RAM: 30%");
  tft.setCursor(boxX + 5, boxY + 20);
  tft.println("ROM: 50%");
  tft.setCursor(boxX + 5, boxY + 35);
  tft.println("CPU: 70%");
}

