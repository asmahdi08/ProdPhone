#include <TFT_eSPI.h>
#include <Arduino.h>
#include "TestScreen.h"
#include "./Drawers.h"

void TestScreen::draw() {
    // Implement drawing code for the test screen
    pp_drawText("Test Screen", 64, 90,
        TFT_GREEN,
        3,
        TFT_BLACK,
        TL_DATUM
    );
}

void TestScreen::update() {
    // Implement update code for the test screen
}

void TestScreen::handleNavigation() {
    // Implement navigation handling for the test screen
}
