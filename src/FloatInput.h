#pragma once
#include "ofMain.h";
#include "SmallButton.h";
#include "Knob.h";
#include "Touchable.h";

class FloatInput : public Touchable
{
    float& value;
    string label;
    Knob dragController;
    ofTrueTypeFont openSans;

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _min, float _max) 
        : value(v),  
        dragController(v, _x, _y + 20, 70, 75, _min, _max)
    {
        label = _label;
        x = _x;
        y = _y;
        w = 70;
        h = 95;
        openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
    };

    void display();
    bool mousePressed();
    bool mouseReleased();
};
