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
    
    //SmallButton plusButton;
    //SmallButton lessButton;

    void update();

public:
     
    FloatInput(float& v, string _label, float _x, float _y, float _step, float _min, float _max) 
        : value(v),  
        dragController(v, _x, _y + 20, w, 30)
    {
        label = _label;
        step = _step;
        x = _x;
        y = _y;
        max = _max;
        min = _min;
        //lessButton = SmallButton(x + 20, y+40, 20);
        //plusButton = SmallButton(x + 45, y+40, 20);
    };

    void modifyValue();
    bool isOver();
    void display();
    bool mousePressed();
    bool mouseReleased();
};
