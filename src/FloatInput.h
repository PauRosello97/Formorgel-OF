#pragma once
#include "ofMain.h";
#include "SmallButton.h";
#include "Knob.h";

class FloatInput
{
    float& value;
    float x, y;
    float w = 70;
    float h = 95;
    string label;
    Knob dragController;
    ofTrueTypeFont openSans;

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _min, float _max) 
        : value(v),  
        dragController(v, _x, _y + 20, w, h-20, _min, _max)
    {
        label = _label;
        x = _x;
        y = _y;
        openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
    };

    bool isOver();
    void display();
    bool mousePressed();
    bool mouseReleased();
};
