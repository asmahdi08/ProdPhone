#pragma once
#include "../Screen.h"
#include <TFT_eSPI.h>

class TestScreen : public Screen {
private:
    uint8_t currentY = 25;
    int8_t lineHeight = 8; // size 4 font height + spacing
public:
    void draw() override;
    void update() override;
    int16_t handleNavigation() override;
};