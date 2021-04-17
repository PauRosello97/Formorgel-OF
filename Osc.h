#pragma once
#include "ofMain.h"
#include "FloatInput.h"

class Osc
{
    FloatInput floatInput;
    float x = 10, y = 10, h = 100, w = 100;
    float value;
    
    //float angle = ofRandom(90);

public:
    Osc() : value(50), floatInput(value) {};
    Osc(float _x, float _y) : value(50), floatInput(value)
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

    void mousePressed() {
        if (isOver()) {
            floatInput.modify_value();
            cout << "hi";
        }        
    }

    bool isOver();

    float get_value() const {
        return value;
    }
};

