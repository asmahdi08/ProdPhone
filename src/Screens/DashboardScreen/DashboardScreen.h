#pragma once
#include "../Screen.h"
#include <TFT_eSPI.h>
#include "../ScreenManager.h"

class DashboardScreen : public Screen {
private:
    unsigned long lastUpdate = 0;  // Track last update time
    String lastTimeString = "";    // Track if time actually changed
    uint8_t currentY = 25;
    int8_t lineHeight = 8; // size 4 font height + spacing
public:
    void draw() override;
    void update() override;
    int16_t handleNavigation() override;
};