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
    string label;
    SmallButton plusButton;
    SmallButton lessButton;

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _step) : value(v) {
        label = _label;
        step = _step;
        x = _x;
        y = _y;
        lessButton = SmallButton(x + 150, y+h/2, 20);
        plusButton = SmallButton(x + 175, y + h / 2, 20);
    };

    void modifyValue() {
        if (plusButton.isOver()) {
            value += step;
        }
        else if (lessButton.isOver()) {
            value -= step;
        }
    }

    bool isOver();
    void display();
    bool mousePressed();
};
