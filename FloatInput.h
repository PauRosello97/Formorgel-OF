#pragma once
#include "ofMain.h"

class FloatInput
{
    float& value;
    float x, y;
    float w = 150;
    float h = 30;
    string label;

public:
     
    FloatInput(float& v, string _label, float _x, float _y) : value(v) {
        label = _label;
        x = _x;
        y = _y;
    };

    void modifyValue() {
        value++;
    }

    bool isOver();
    void display();
    void mousePressed();
};
