#pragma once
#include "ofMain.h"

class SmallButton {
    float x, y;
    float size = 20;
    ofColor color;
public:
    SmallButton() {};
    SmallButton(float _x, float _y, float _size) {
        x = _x;
        y = _y;
        size = _size;
        color = ofColor(20);
    };
    SmallButton(float _x, float _y, float _size, ofColor _color) {
        x = _x;
        y = _y;
        size = _size;
        color = _color;
    };
    void display() {
        ofSetColor(color);
        if (isOver()) {
            ofSetColor(255, 0, 0);
        }
        ofDrawRectangle(x-size/2, y-size/2, size, size);
    }
    bool isOver() {
        return ofGetMouseX() > x-size/2 && ofGetMouseX() < x + size/2 && ofGetMouseY() > y-size/2&& ofGetMouseY() < y + size/2;
    }
    void setColor(ofColor _color) {
        color = _color;
    }
    ofColor getColor() {
        return color;
    }
};
