#pragma once
#include "ofMain.h"

class FloatInput
{
    float& value;

public:
    FloatInput(float& v) : value(v) {};

    void modify_value() {
        value++;
    }

    void display(float x, float y) {
        ofSetColor(0, 0, 0);
        ofDrawBitmapString("AngleINPUT: " + ofToString(value), x + 10, y + 20);
        ofSetColor(120, 120, 120);
        ofDrawRectangle(x, y, 150, 30);
    }
};
