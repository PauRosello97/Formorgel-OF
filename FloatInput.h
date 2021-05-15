#pragma once
#include "ofMain.h";
#include "SmallButton.h";

class FloatInput
{
    float& value;
    float x, y;
    float w = 190;
    float h = 30;
    float step = 0;
    float max, min;
    string label;
    SmallButton plusButton;
    SmallButton lessButton;

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _step, float _min, float _max) : value(v) {
        label = _label;
        step = _step;
        x = _x;
        y = _y;
        max = _max;
        min = _min;
        lessButton = SmallButton(x + 150, y+h/2, 20);
        plusButton = SmallButton(x + 175, y + h / 2, 20);
    };

    void modifyValue();
    bool isOver();
    void display();
    bool mousePressed();
};
