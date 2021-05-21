#pragma once
#include "ofMain.h";
#include "SmallButton.h";
#include "DragController.h";

class FloatInput
{
    float& value;
    float x, y;
    float w = 70;
    float h = 85;
    string label;
    DragController dragController;

    void update();

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _min, float _max) 
        : value(v),  
        dragController(v, _x, _y + 20, w, h-20, _min, _max)
    {
        label = _label;
        x = _x;
        y = _y;
    };

    bool isOver();
    void display();
    bool mousePressed();
    bool mouseReleased();
};
