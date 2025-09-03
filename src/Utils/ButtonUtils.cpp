#include "ButtonUtils.h"

// Define static member variables
int8_t l_p_count = 0;
int8_t r_p_count = 0;

bool ButtonUtils::isLeftButtonPressed() {
    static unsigned long lastPress = 0;
    unsigned long now = millis();

    if (digitalRead(L_BTN_PIN) == LOW) {
        if (now - lastPress > 400) { // 400ms debounce
            lastPress = now;
            return true;
        }
    }
    return false;
}


bool ButtonUtils::isRightButtonPressed() {
    static unsigned long lastPress = 0;
    unsigned long now = millis();

    if (digitalRead(R_BTN_PIN) == LOW) {
        if (now - lastPress > 400) { // 400ms debounce
            lastPress = now;
            return true;
        }
    }
    return false;
}
