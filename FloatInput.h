#pragma once
#include "ofMain.h";
#include "SmallButton.h";

class FloatInput
{
    float& value;
    float x, y;
    float w = 190;
    float h = 30;
    string label;
    SmallButton plusButton;
    SmallButton lessButton;

public:
     
    FloatInput(float& v, string _label, float _x, float _y) : value(v) {
        label = _label;
        x = _x;
        y = _y;
        lessButton = SmallButton(x + 150, y+h/2);
        plusButton = SmallButton(x + 175, y + h / 2);
    };

    void modifyValue() {
        if (plusButton.isOver()) {
            value++;
        }
        else if (lessButton.isOver()) {
            value--;
        }
        
    }

    bool isOver();
    void display();
    bool mousePressed();
};
