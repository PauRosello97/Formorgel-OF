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
    float radians(float degrees);
    
public:
    Osc() : 
        value(50), 
        offsetInput(offset, "Offset", 0, 0, 1),
        angleInput(angle, "Angle", 0, 0, 1),
        lengthInput(length, "Length", 0, 0, 1) 
    {};

    Osc(float _x, float _y, float _w) : 
        value(50), 
        offsetInput(offset, "Offset", _x+_w/2, _y+10, 0.2),
        angleInput(angle, "Angle", _x+_w/2, _y+50, 1),
        lengthInput(length, "Length", _x+_w/2, _y+90, 0.1)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _w/2;
    }

    float offset = 0;
    float angle = round(ofRandom(90));
    float length = 2;

    void display();
    bool isOver();
    bool mousePressed();    

    float get_value() const {
        return value;
    }
};

