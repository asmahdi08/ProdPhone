#pragma once
#include "Screen.h"

class ScreenManager {
private:
    Screen* currentScreen;
public:
    ScreenManager() : currentScreen(nullptr) {}

    void setScreen(Screen* screen) {
        currentScreen = screen;
        if (currentScreen) {
            currentScreen->init(); // initialize new screen
        }
    }

    void draw(){
        if(currentScreen) {
            currentScreen->draw();
        }
    }

    void update(){
        if(currentScreen) {
            currentScreen->update();
        }
    }

    int16_t handleNavigation(){
        if(currentScreen) {
            return currentScreen->handleNavigation();
        }
        return -1;
    }
};