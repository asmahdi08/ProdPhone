#include <TFT_eSPI.h>
#include <Arduino.h>
#include "TestScreen.h"
#include "./Drawers.h"
#include "./Definitions.h"
#include "../../Utils/ButtonUtils.h"

ButtonUtils buttonUtils;

void TestScreen::draw() {
    // Implement drawing code for the test screen
    pp_drawBox(0,currentY,128,180,TFT_BLACK,TFT_BLACK, 0,false);
    pp_drawText("Test", 64, 90,
        TFT_GREEN,
        3,
        TFT_BLACK,
        MC_DATUM
    );
}

void TestScreen::update() {
    // Implement update code for the test screen
}

int16_t TestScreen::handleNavigation() {
    if(ButtonUtils::isLeftButtonPressed()) {
        Serial.println("Left button pressed - Navigate to previous screen");
        // move to next screen
        return 0;
    }
    if(ButtonUtils::isRightButtonPressed()) {
        Serial.println("Right button pressed - Navigate to next screen");
        // move to next screen
        return 0;
    }
    return -1;
}
