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
        offsetInput(offset, "Offset", 0, 0, 0, 0.5),
        angleInput(angle, "Angle", 0, 0, 0, 360),
        lengthInput(length, "Length", 0, 0, 0.5, 1.5) 
    {};

    Osc(float _x, float _y, float _w) : 
        value(50), 
        offsetInput(offset, "Offset", _x+_w/2, _y+10, 0, 0.5),
        angleInput(angle, "Angle", _x+_w/2 + 100, _y+10, 0, 360),
        lengthInput(length, "Length", _x+_w/2, _y+105, 0.5, 1.5)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _w/2;
        offset = round(ofRandom(100)) / 100;
        angle = round(ofRandom(90));
        length = round(50 + ofRandom(100)) / 100;
    }

    Osc(float _x, float _y, float _w, float _offset) :
        value(50),
        offsetInput(offset, "Offset", _x + _w / 2, _y + 10, 0, 0.5),
        angleInput(angle, "Angle", _x+_w/2+100, _y + 10, 0, 360),
        lengthInput(length, "Length", _x + _w / 2, _y + 105, 0.5, 1.5)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _w / 2;
        offset = _offset;
        angle = round(ofRandom(90));
        length = round(50 + ofRandom(100)) / 100;
    }

    float offset, angle, length;

    void display();
    bool isOver();
    bool mousePressed();   
    bool mouseReleased();
    void randomize();

    float get_value() const {
        return value;
    }
};

