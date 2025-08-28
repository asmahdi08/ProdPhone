#include "DashboardScreen.h"
#include "./Drawers.h"
#include "./Definitions.h"
#include "time.h"
#include <TFT_eSPI.h>
#include <Arduino.h>
#include "../../Utils/TimeUtils.h"   // relative path
#include "../ScreenManager.h"
#include "../TestScreen/TestScreen.h"

extern TFT_eSPI tft;

namespace {
    float getFreeRamPercentage(){
        uint32_t freeHeap = ESP.getFreeHeap();
        uint32_t totalHeap = ESP.getHeapSize();

        return (((totalHeap-freeHeap)*100.0f) / totalHeap);
    }
}

void DashboardScreen::draw(){
    
    // Implement drawing code for the dashboard screen

    uint8_t currentY = 25;
    int8_t lineHeight = 8; // size 4 font height + spacing

    // Display current time
    String currentTime = TimeUtils::getCurrentTime();
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
    currentY = 108;

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

void DashboardScreen::update() {
unsigned long now = millis();  // Get current time

if (now - lastUpdate >= 1000) { // Check if 1 second passed
    lastUpdate = now;
    String currentTimeStr = TimeUtils::getCurrentTime();
    
    // Only update if time actually changed
    if (currentTimeStr != lastTimeString) {
        lastTimeString = currentTimeStr;
        
        // Clear the specific areas where time is displayed
                
        // Main time display (large) 
        tft.fillRect(20, 25, 88, 32, TFT_BLACK); // Clear old time area
        pp_drawText(currentTimeStr, 64, 25, TFT_GREEN, 4, TFT_BLACK, TC_DATUM);
    }
}
}

void DashboardScreen::handleNavigation(){
    if(digitalRead(L_BTN_PIN) == LOW) {
        Serial.println("Left button pressed - Navigate to previous screen");
        // move to next screen
    }else if(digitalRead(R_BTN_PIN) == LOW) {
        Serial.println("Right button pressed - Navigate to next screen");
        // move to next screen
    }
    //screenM.draw();
}
