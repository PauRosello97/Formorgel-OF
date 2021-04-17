#pragma once
#include "ofMain.h"
#include "FloatInput.h"

class Osc
{
    FloatInput offsetInput;
    FloatInput angleInput;
    FloatInput lengthInput;
    float x = 10, y = 10, h = 100, w = 100;
    float value;
    
public:
    Osc() : 
        value(50), 
        offsetInput(offset, "Offset", x+10, y+10),
        angleInput(angle, "Angle", x+10, y+75),
        lengthInput(length, "Length", x + 10, y + 125) {};

    Osc(float _x, float _y) : 
        value(50), 
        offsetInput(offset, "Offset", _x+10, _y+10),
        angleInput(angle, "Angle", _x + 10, _y + 75),
        lengthInput(length, "Length", _x + 10, _y + 125)
    {
        x = _x;
        y = _y;
        w = 300;
        h = 200;
    }

    float offset = 0;
    float angle = ofRandom(90);
    float length = 2;

    void display();
    bool isOver();
    bool mousePressed();

    float get_value() const {
        return value;
    }
};

