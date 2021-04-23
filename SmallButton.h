#pragma once
#include "ofMain.h"

class SmallButton {
    float x, y;
    float size = 20;
public:
    SmallButton() {};
    SmallButton(float _x, float _y) {
        x = _x;
        y = _y;
    };
    void display() {
        ofSetColor(20, 20, 20);
        if (isOver()) {
            ofSetColor(255, 0, 0);
        }
        ofDrawRectangle(x-size/2, y-size/2, size, size);
    }
    bool isOver() {
        return ofGetMouseX() > x-size/2 && ofGetMouseX() < x + size/2 && ofGetMouseY() > y-size/2&& ofGetMouseY() < y + size/2;
    }
};
