#pragma once

#include <map>

class Screen {
public:
    virtual void draw() = 0;     // must be implemented
    virtual void update() {}     // optional
    virtual void init() {}
    virtual void handleInput() {}
    virtual int16_t handleNavigation() {}
    //virtual uint16_t getScreenId() const { return 0; } // optional, default to 0
};