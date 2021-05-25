#pragma once
#include "ofMain.h"

class SmallButton {
    float x, y;
    float size = 20;
    ofColor color;
public:
    SmallButton() {};
    SmallButton(float _x, float _y, float _size);
    SmallButton(float _x, float _y, float _size, ofColor _color);
    void display();
    bool isOver();
    void setColor(ofColor _color);
    ofColor getColor();
};
