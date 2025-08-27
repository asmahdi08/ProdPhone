#pragma once

class Screen {
public:
    virtual void draw() = 0;     // must be implemented
    virtual void update() {}     // optional
};