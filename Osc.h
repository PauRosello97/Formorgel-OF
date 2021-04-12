#pragma once
#include "ofMain.h"
#include "FloatInput.h"

class Osc
{
    FloatInput b;
    float x, y, h, w;
    float value;
    float angle = ofRandom(90);

public:
    Osc() : value(50), b(value) {};
    Osc(float _x, float _y, float _w, float _h) : value(50), b(value)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }

    void display();

    void modify_value() {
        b.modify_value();
    }

    float get_value() const {
        return value;
    }
};

