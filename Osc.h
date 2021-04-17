#pragma once
#include "ofMain.h"
#include "FloatInput.h"

class Osc
{
    FloatInput offsetInput;
    float x = 10, y = 10, h = 100, w = 100;
    float value;
    
    //float angle = ofRandom(90);

public:
    Osc() : value(50), offsetInput(offset) {};
    Osc(float _x, float _y) : value(50), offsetInput(value)
    {
        x = _x;
        y = _y;
        w = 200;
        h = 200;
    }

    float offset = 0;
    float angle = ofRandom(90);
    float length = 2;

    void display();

    bool mousePressed() {
        if (isOver()) {
            offsetInput.modify_value();
            return true;
        }
        else {
            return false;
        }
    }

    bool isOver();

    float get_value() const {
        return value;
    }
};

