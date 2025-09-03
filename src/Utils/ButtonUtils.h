#pragma once

#include <Arduino.h>
#include "../Definitions.h"

class ButtonUtils {
private:
    static bool lastLeftState;
    static bool lastRightState;

public:
    static bool isLeftButtonPressed();
    static bool isRightButtonPressed();
};