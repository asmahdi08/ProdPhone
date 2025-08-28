#pragma once

#include <map>

class Screen {
public:
    virtual void draw() = 0;     // must be implemented
    virtual void update() {}     // optional
    virtual void init() {}
    virtual void handleInput() {}
    virtual void handleNavigation() {}

protected:
};