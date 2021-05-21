#pragma once
#include "ofMain.h";
#include "SmallButton.h";
#include "DragController.h";

class FloatInput
{
    float& value;
    float x, y;
    float w = 100;
    float h = 50;
    float step = 0;
    float max, min;
    string label;
    DragController dragController;

    void update();

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _step, float _min, float _max) 
        : value(v),  
        dragController(v, _x, _y + 20, w, 20, _step, _min, _max)
    {
        label = _label;
        step = _step;
        x = _x;
        y = _y;
        max = _max;
        min = _min;
    };

    void modifyValue();
    bool isOver();
    void display();
    bool mousePressed();
    bool mouseReleased();
};
